#include <iostream>
#include <Windows.h>
#include "memory.h"
#include "Offsets.h"
#include <thread>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



//variables 

void Attach();	


//

int main()
{
	std::cout << "GTFO Menu \n";

	Attach();
	std::this_thread::sleep_for(std::chrono::seconds(1));

	system("cls");
	std::cout << "GTFO Menu \n";
	std::cout << "[+] Press F2 to toggle Infinity Ammo \n";

	std::this_thread::sleep_for(std::chrono::seconds(1));
	while (true) {

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			static bool infinityAmmoEnabled = false;

			infinityAmmoEnabled = !infinityAmmoEnabled;
			system("cls");
			features::toogleinfinityAmmo(infinityAmmoEnabled);

			if (!infinityAmmoEnabled) // só toca quando ativa
			{
				// fecha se já estava aberto antes
				mciSendString("close mySound", NULL, 0, NULL);

				// abre e toca o som
				mciSendString("open \"bin\\SE.mp3\" type mpegvideo alias mySound", NULL, 0, NULL);
				mciSendString("play mySound", NULL, 0, NULL);
			}
		}

	}

	system("pause");
	return 0;
}


void Attach()
{
	std::cout << "[+] Attaching to GTFO... \n";

	HWND hwnd  = FindWindowA(NULL, "GTFO");
	if( hwnd == NULL)
	{
		std::cout << "[-] GTFO not running! \n";
		exit(0);
	}
	else {
		std::cout << "[+] Found GTFO! \n";
	}


	if(memory::processid = memory::GetProcId("GTFO.exe")){
		std::cout << "[+] Found GTFO process id: " << memory::processid << "\n";
	}
	else
	{
		std::cout << "[-] Failed to find GTFO process id! \n";
		exit(0);
	}


	memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, memory::processid);
	if (memory::hProcess == NULL)
	{
		std::cout << "[-] Failed to open GTFO process! \n";
		exit(0);
	}
	else
	{
		std::cout << "[+] Successfully opened GTFO process! \n";
	}


	memory::ModuleBase = memory::GetModuleBase("GTFO.exe",memory::processid);
	memory::clientModule = memory::GetModuleBase("GameAssembly.dll", memory::processid);


	if (memory::ModuleBase == NULL)
	{
		std::cout << "[-] Failed to get module base! \n";
		exit(0);
	}
	else
	{
		std::cout << "[+] Successfully attached to GTFO! \n";
	}


	std::cout << "[+] Module Base: " << std::hex << memory::ModuleBase << std::dec << "\n";
	std::cout << "[+] Process ID: " << memory::processid << "\n";
	std::cout << "[+] GameAssembly.dll Base: " << std::hex << memory::clientModule << std::dec << "\n";

	std::cout << "[+] get intro the cheat menu! \n";

}

