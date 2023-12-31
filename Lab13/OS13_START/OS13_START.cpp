﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "HT_LIB.h"
#include <wchar.h>

wchar_t* GetWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

int main(int argc, char* argv[])
{
	OS13HANDEL ht = nullptr;

	wchar_t* fileName{ nullptr };
	const std::wstring directoryPath = L"..\\..\\HashTables";
	std::wstring filePath(L"..\\HashTables\\HT.ht");

	try {

		if (argv[1]) 
		{
			fileName = GetWC(argv[1]);
			std::wstring s(directoryPath);
			s += L"\\" + std::wstring(fileName);
			filePath = s;
		}
		else
			std::cout << "Using default file path" << std::endl;

		std::wstring eventName{ fileName };
		eventName += L"E";
		HANDLE hStopEvent = CreateEvent(NULL,
			TRUE,
			FALSE,
			eventName.c_str());


		ht = HT_LIB::Init();
		if (ht == NULL)
			throw "Error init com";

		if(!HT_LIB::HT::Open(ht, filePath.c_str()))
			throw "Error open";
		std::cout << "-- HT-Storage Open " << std::endl;
		while (WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT)
		{
		}

		HT_LIB::Dispose(ht);
		return 0;
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
		return 1;
	}
}
