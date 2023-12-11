#pragma once
#include "IHT.h"
#include "HTHandle.h"
#include <initguid.h>

extern long g_lObjs;
extern long g_lLocks;

extern LPCWSTR  FriendlyName;
extern LPCWSTR  VerIndProg;
extern LPCWSTR  ProgID;

// {89FAEAD7-E398-4215-8DB0-E052A63B944F}
DEFINE_GUID(IID_IHT,
	0x89faead7, 0xe398, 0x4215, 0x8d, 0xb0, 0xe0, 0x52, 0xa6, 0x3b, 0x94, 0x4f);

// {3C872F0B-33D1-4C18-AF3D-D3F341CB577D}
DEFINE_GUID(CLSID_HT,
	0x3c872f0b, 0x33d1, 0x4c18, 0xaf, 0x3d, 0xd3, 0xf3, 0x41, 0xcb, 0x57, 0x7d);

class HT : public IHT
{
public:
	HT();
	~HT();

	STDMETHOD(QueryInterface(const IID& riid, void** ppvObject));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	STDMETHOD_(HTHANDLE*, Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const std::wstring HTUsersGroups, const std::wstring FileName));
	STDMETHOD(Open(const std::wstring FileName));
	STDMETHOD(Open(const std::wstring HTUser, const std::wstring HTPassword, const std::wstring FileName));
	STDMETHOD_(HTHANDLE*, OpenExist(const std::wstring FileName));
	STDMETHOD_(HTHANDLE*, OpenExist(const std::wstring HTUser, const std::wstring HTPassword, const std::wstring FileName));
	STDMETHOD(CloseExist(const HTHANDLE* hthandle));
	STDMETHOD(Snap(HTHANDLE* hthandle));
	STDMETHOD(Insert(HTHANDLE* hthandle, Element* element));
	STDMETHOD(Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlenth));
	STDMETHOD(Delete(HTHANDLE* hthandle, Element* element));
	STDMETHOD(Close(const HTHANDLE* htHandle));
	STDMETHOD_(Element*, Get(HTHANDLE* hthandle, Element* element));
	STDMETHOD_(char*, GetLastErrorProg(HTHANDLE* ht));
	STDMETHOD(print(const Element* element));
	STDMETHOD_(Element*, CreateNewKeyElement(const void* key, int keylength));
	STDMETHOD_(Element*, CreateNewFullElement(const void* key, int keylength, const void* payload, int payloadlength));

	static void SetErrorMessage(HTHANDLE* ht, const char* message, int messageLen);

private:
	int HashFunction(const Element* element, int size, int p);
	int Next_hash(int hash, int size, int p);
	wchar_t* GenerateMutexName(const wchar_t* pathToHT);
	wchar_t* GenerateViewName(const wchar_t* pathToHT);
	BOOL CheckParmLength(HTHANDLE* ht, Element* element);
	BOOL CheckParmLength(HTHANDLE* ht, int payloadLength);
	Element* GetElementFromHT(HTHANDLE* ht, int n);
	BOOL SetElementToHT(HTHANDLE* ht, Element* element, int n);
	BOOL IsDeleted(Element* ptr);
	void SetDeletedFlag(Element* ptr);
	BOOL EqualElementKeys(Element* el1, Element* el2);
	void UpdateElement(HTHANDLE* ht, Element* el, void* newpayload, int newpayloadlength);
	BOOL CheckCurrentUser(HTHANDLE*, const wchar_t UserName[512] = NULL, const wchar_t UserGroup[512] = NULL);

	const int DELETED = -1;
	LONG m_refCount;
};