#pragma once //com объект
#include "IHT.h"
#include "HTHandle.h"
#include <initguid.h>

extern long g_lObjs;
extern long g_lLocks;

extern LPCWSTR  FriendlyName;
extern LPCWSTR  VerIndProg;
extern LPCWSTR  ProgID;

// {4F27F112-AAA2-4AE7-B561-05FE64797ABD}
DEFINE_GUID(IID_IHT,
	0x4f27f112, 0xaaa2, 0x4ae7, 0xb5, 0x61, 0x5, 0xfe, 0x64, 0x79, 0x7a, 0xbd);

// {3ABFF639-5E84-4D55-8655-2A685D067EBF}
DEFINE_GUID(CLSID_HT,
	0x3abff639, 0x5e84, 0x4d55, 0x86, 0x55, 0x2a, 0x68, 0x5d, 0x6, 0x7e, 0xbf);


class HT : public IHT
{
public:
	HT();
	~HT();

	STDMETHOD(QueryInterface(const IID& riid, void** ppvObject));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	STDMETHOD_(HTHANDLE*, Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const std::wstring FileName));
	STDMETHOD(Open(const std::wstring FileName));
	STDMETHOD_(HTHANDLE*, OpenExist(const std::wstring FileName));
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

	const int DELETED = -1;
	LONG m_refCount;
};