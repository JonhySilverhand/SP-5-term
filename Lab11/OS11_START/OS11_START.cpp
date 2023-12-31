﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "../OS11_HTAPI/HT.h"

using namespace std;
using namespace HT;

int main(int argc, char* argv[])																													 // D:\University\осисп\labs\OS11\x64\Debug>OS11_START ./files/os11_create.ht
{
	HMODULE libModule = NULL;
	try
	{
		HMODULE libModule = LoadLibrary(L"OS11_HTAPI");
		if (!libModule)
		{
			throw "Unable to load library";
		}
		if (argc != 2)
		{
			throw "Enter two arguments";
		}
		const size_t cSize = strlen(argv[1]) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, argv[1], cSize);

		HTHandle* HT = Open(wc);
		if (HT == NULL)
		{
			throw "Storage not created";
		}

		cout << "Storage Start..." << endl;
		wcout << "filename = " << wc << endl;
		cout << "snapshotinterval = " << HT -> SecSnapshotInterval << endl;
		cout << "capacity = " << HT -> Capacity << endl;
		cout << "maxkeylength = " << HT -> MaxKeyLength << endl;
		cout << "maxdatalength = " << HT -> MaxPayloadLength << endl;

		while (true) 
		{
			Sleep((HT->SecSnapshotInterval) * 1000);
			Snap(HT);
			cout << "=========SNAPSHOT=========" << endl;
		}
		Snap(HT);
		Close(HT);
		FreeLibrary(libModule);
	}
	catch (const char* err)
	{
		cout << err << endl;
		FreeLibrary(libModule);
		return -1;
	}

	return 0;
}