// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Registry.h"
#include <fstream>

HMODULE hSvyCA;
LONG Seq = 0;
std::fstream LogCOM;

ULONG g_Components = 0;
ULONG g_ServerLocks = 0;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    setlocale(LC_ALL, "Rus");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hSvyCA = hModule;
        LogCOM.open("C:\\University\\5_term\\СП\\Lab15\\log.txt", std::ios_base::out);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

