#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <string>
#include "sddl.h"

#include "../OS15_HTCOM_LIB/pch.h"
#include "../OS15_HTCOM_LIB/OS15.h"

#define SERVICENAME L"OS15_HTService"
#define HTPATH L"D:/University/5th_term/ÑÏ/Lab15/Lab15/HashStorage/HT.ht"

#define USERNAME L"HTUser01"
#define PASSWORD L"12345"

#define TRACEPATH L"D:/University/5th_term/ÑÏ/Lab15/Lab15/HashStorage/service.trace"

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

SECURITY_ATTRIBUTES getSecurityAttributes();
HANDLE createStopEvent(const wchar_t* stopEventName);
void startService();
void trace(const char* msg, int r = std::ofstream::app);