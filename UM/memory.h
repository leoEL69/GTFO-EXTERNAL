#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

namespace memory
{	


	inline HANDLE hProcess;
	inline uintptr_t processid;
	inline uintptr_t ModuleBase;
	inline uintptr_t clientModule;

    inline uintptr_t GetModuleBase(const char* modName, DWORD procId)
    {
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

        if (hSnap != INVALID_HANDLE_VALUE)
        {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);

            if (Module32First(hSnap, &modEntry))
            {
                do
                {
                    if (_stricmp(modEntry.szModule, modName) == 0) // compara sem case
                    {
                        modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
        CloseHandle(hSnap);
        return modBaseAddr;
    }


    inline DWORD GetProcId(const char* procName)
    {
        DWORD procId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE)
        {
            PROCESSENTRY32 procEntry;
            procEntry.dwSize = sizeof(procEntry);

            if (Process32First(hSnap, &procEntry))
            {
                do
                {
                    if (_stricmp(procEntry.szExeFile, procName) == 0) 
                    {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32Next(hSnap, &procEntry));
            }
        }
        CloseHandle(hSnap);
        return procId;

    }

	template <class T>
	inline T Read(HANDLE hProcess, uintptr_t address)
	{
		T value{};
		ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &value, sizeof(T), nullptr);
		return value;
	}

   inline bool Write(HANDLE hProcess, uintptr_t address, const void* buffer, size_t size)
   {
        return WriteProcessMemory(hProcess, (LPVOID)address, buffer, size, nullptr);
   }

}
