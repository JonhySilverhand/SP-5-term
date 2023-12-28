#pragma once
#include <objbase.h>

// {CFB9F3BE-CD02-4722-8807-2C4F7D77A05F}
static const GUID CLSID_CA =
{ 0xcfb9f3be, 0xcd02, 0x4722, { 0x88, 0x7, 0x2c, 0x4f, 0x7d, 0x77, 0xa0, 0x5f } };


extern HMODULE hSvyCA;

static LPCWSTR FNAME = L"SP15.HTCOM";
static LPCWSTR VINDX = L"SP15.v1";
static LPCWSTR PRGID = L"SP15";

STDAPI DllInstall(BOOL b, PCWSTR s);
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();


HRESULT RegisterServer(HMODULE hModule,            // DLL module handle
	const CLSID& clsid,         // Class ID
	const WCHAR* szFriendlyName, // Friendly Name
	const WCHAR* szVerIndProgID, // Programmatic
	const WCHAR* szProgID);     //   IDs

HRESULT UnregisterServer(const CLSID& clsid,
	const WCHAR* szVerIndProgID,
	const WCHAR* szProgID);