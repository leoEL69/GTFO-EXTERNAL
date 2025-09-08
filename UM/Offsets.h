#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include "memory.h"

namespace addr {

	inline uintptr_t infinityAmmo;


}



namespace features
{
	inline void toogleinfinityAmmo(bool enable) {


		 
		addr::infinityAmmo = memory::clientModule + 0x53A6B2; // GameAssembly.dll +0x53A6B2
	

		memory::Read<uintptr_t>(memory::hProcess, addr::infinityAmmo);
		std::cout << "[+] Infinity Ammo Address: " << std::hex << addr::infinityAmmo << "\n";

		BYTE originalBytes[6] = { 0xFF,0x8B,0x90,0x02,0x00,0x00 };
		BYTE nop[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
        // buffer para armazenar bytes atuais
        BYTE current[6]{};

        if (enable)
        {
            // só restaura se não estiver com os bytes originais
            if (memcmp(current, originalBytes, sizeof(originalBytes)) != 0)
            {
                memory::Write(memory::hProcess, addr::infinityAmmo, originalBytes, sizeof(originalBytes));
                std::cout << "[+] Disabled Infinity Ammo (restored original) \n";
            }
            else
            {
                std::cout << "[*] Infinity Ammo já está desabilitado. \n";
            }
        }
        else
        {
            // só patcha se ainda não estiver NOPado
            if (memcmp(current, nop, sizeof(nop)) != 0)
            {
                memory::Write(memory::hProcess, addr::infinityAmmo, nop, sizeof(nop));
                std::cout << "[+] Enabled Infinity Ammo (NOP patch applied) \n";
            }
            else
            {
                std::cout << "[*] Infinity Ammo já está habilitado. \n";
            }
        }

	}




}

