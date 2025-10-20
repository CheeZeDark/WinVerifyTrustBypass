#pragma once
#include <iostream>
#include <Windows.h>
#include <MinHook.h>
using namespace std;

void CreateConsole()
{
	FILE* fp;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
	SetConsoleTitleA("WinVerifyTrust Hooker by CheeZeDark(Rikko Matsumato)");
}

namespace Hook 
{
	using WinVerifyTrustFn = LONG(__stdcall*)(HWND, GUID*, LPVOID);
	WinVerifyTrustFn oWinVerifyTrustFn;
	LONG hkWinVerifyTrust(HWND hwnd, GUID* pgActionID, LPVOID pWVTData) {
		oWinVerifyTrustFn(hwnd, pgActionID, pWVTData); //Just for Testing if Function is Successfully Initializated!!! If Doesn't Worked, you need to bypass somehow...
		cout << "[WinVerifyBypass] Successfully Called WinVerifyTrust Function" << endl;
		return 0;
	}
	void InitMinhookAndHookWinVerifyTrust() 
	{
		if (MH_Initialize() == MH_OK) {
			cout << "Successfully Initializated MinHook" << endl;
		}
		else {
			throw std::runtime_error("Failed to Init Minhook!!!");
		}
		if (MH_CreateHookApi(L"wintrust", "WinVerifyTrust", hkWinVerifyTrust, reinterpret_cast<void**>(oWinVerifyTrustFn)) == MH_OK) {
			cout << "[WinVerifyTrustBypass] Successfully Hooked WinVerifyTrust Function." << endl;
		}
	}

}

