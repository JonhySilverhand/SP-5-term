//#define _CRT_SECURE_NO_WARNINGS
#include "REGISTRY.h"
//#include <iostream>
//#include "SEQLOG.h"

BOOL setKeyAndValue(const WCHAR* szKey,
	const WCHAR* szSubkey,
	const WCHAR* szValue);

void CLSIDtochar(const CLSID& clsid,
	WCHAR* szCLSID,
	int length);

LONG recursiveDeleteKey(HKEY hKeyParent, const WCHAR* szKeyChild); // Delete szKeyChild and all of its descendents.

const int CLSID_STRING_SIZE = 39;

HRESULT RegisterServer(HMODULE hModule,            // DLL module handle
	const CLSID& clsid,         // Class ID
	const WCHAR* szFriendlyName, // Friendly Name
	const WCHAR* szVerIndProgID, // Programmatic
	const WCHAR* szProgID)       //   IDs
{

	WCHAR sizeModule[512];
	DWORD dwResult = GetModuleFileName(hModule, sizeModule, sizeof(sizeModule) / sizeof(WCHAR));
	assert(dwResult != 0);

	WCHAR szCLSID[CLSID_STRING_SIZE];
	CLSIDtochar(clsid, szCLSID, sizeof(szCLSID));

	WCHAR sizeKey[264];      //smw sizeKey[64]
	wcscpy_s(sizeKey, L"CLSID\\");
	wcscat_s(sizeKey, szCLSID);

	setKeyAndValue(sizeKey, NULL, szFriendlyName);
	setKeyAndValue(sizeKey, L"InprocServer32", sizeModule);
	setKeyAndValue(sizeKey, L"ProgID", szProgID);
	setKeyAndValue(sizeKey, L"VersionIndependentProgID", szVerIndProgID);
	setKeyAndValue(szVerIndProgID, NULL, szFriendlyName);
	setKeyAndValue(szVerIndProgID, L"CLSID", szCLSID);
	setKeyAndValue(szVerIndProgID, L"CurVer", szProgID);
	setKeyAndValue(szProgID, NULL, szFriendlyName);
	setKeyAndValue(szProgID, L"CLSID", szCLSID);

	return S_OK;
}

HRESULT UnregisterServer(const CLSID& clsid,
	const WCHAR* szVerIndProgID,
	const WCHAR* szProgID)

{
	WCHAR szCLSID[CLSID_STRING_SIZE];
	CLSIDtochar(clsid, szCLSID, sizeof(szCLSID));

	WCHAR szKey[64];
	wcscpy_s(szKey, L"CLSID\\");
	wcscat_s(szKey, szCLSID);

	LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey);
	assert((lResult == ERROR_SUCCESS) || (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID);
	assert((lResult == ERROR_SUCCESS) || (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szProgID);
	assert((lResult == ERROR_SUCCESS) || (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.

	return S_OK;
}


void CLSIDtochar(const CLSID& clsid,      // Convert a CLSID to a char string.   
	WCHAR* szCLSID,						  // smw:char* szCLSID,
	int length)
{
	assert(length >= CLSID_STRING_SIZE);

	LPOLESTR wszCLSID = NULL;
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID);
	assert(SUCCEEDED(hr));
	wcscpy_s(szCLSID, CLSID_STRING_SIZE, wszCLSID);
	CoTaskMemFree(wszCLSID);

}


LONG recursiveDeleteKey(HKEY hKeyParent,           // Parent of key to delete
	const WCHAR* lpszKeyChild)  // Key to delete
{

	HKEY hKeyChild;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
		KEY_ALL_ACCESS, &hKeyChild);
	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	FILETIME time;
	WCHAR sizeBuffer[256];
	DWORD dwSize = 256;
	while (RegEnumKeyEx(hKeyChild, 0, sizeBuffer, &dwSize, NULL,
		NULL, NULL, &time) == S_OK)
	{
		lRes = recursiveDeleteKey(hKeyChild, sizeBuffer);
		if (lRes != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild);
			return lRes;
		}
		dwSize = 256;
	}

	RegCloseKey(hKeyChild);
	return RegDeleteKey(hKeyParent, lpszKeyChild);
}

BOOL setKeyAndValue(const WCHAR* szKey,         // smw:const char* szKey
	const WCHAR* szSubkey,						// smw:const char* szSubkey,
	const WCHAR* szValue)						// smw: const char* szValue
{
	HKEY hKey;
	WCHAR szKeyBuf[1024];

	wcscpy_s(szKeyBuf, szKey);

	if (szSubkey != NULL)
	{
		wcscat_s(szKeyBuf, L"\\");
		wcscat_s(szKeyBuf, szSubkey);
	}
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT,
		szKeyBuf,
		0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL,
		&hKey, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE;
	}

	if (szValue != NULL)
	{
		RegSetValueEx(hKey, NULL, 0, REG_SZ,
			(BYTE*)szValue,
			2 * wcslen(szValue) + 1);
	}

	RegCloseKey(hKey);
	return TRUE;
}