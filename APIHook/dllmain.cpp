// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "MyFunction.h"

extern HINSTANCE hinst;
extern HANDLE hProcess;
extern bool bHook;

bool isInject = false;

void Inject();
void HookOff();
bool checkInjectPid(DWORD pid);
void WriteToFile(const char *str);
void addInjectInfo(wstring szDllName, string szFuncName, void *szNewFunc);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	DWORD dwPid;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		hinst = hModule;
		dwPid = ::GetCurrentProcessId();
		/*if (!checkInjectPid(dwPid)) {	//不使用HOOK注入，则不再需要检测，当使用HOOK注入而又不检测时，每个程序都将会注入此dll
			isInject = false;
			return true;
		}*/
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPid);
		addInjectInfo(L"Kernel32.dll", "CreateFileW", MyCreateFileW);
		addInjectInfo(L"Kernel32.dll", "WriteFile", MyWriteFile);
		//调用注射函数
		Inject();
		//MessageBoxW(NULL, L"inject successful", L"", 0);
		WriteToFile("inject successful");
		isInject = true;
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		// 如果add钩子开着，则将其关闭
		if (bHook)
			HookOff();
		if (!isInject) {
			return true;
		}
		WriteToFile("inject over");
        break;
    }
	
    return TRUE;
}
