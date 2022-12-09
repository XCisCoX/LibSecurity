// Wiz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "resource.h"
#include "..\LibSecurity\CisCo_Header.h"
#pragma comment(lib,"..\\Release\\LibSecurity.lib")

using namespace CISCO;
#define SXE_DEAD_PATH L"C:\\sXe Dead.exe"

int main()
{
	printf("Write ...\n");
	if (!File::extract_resource(SXE_DEAD_PATH, IDR_RCDATA1, RT_RCDATA))
	{
		printf("Can't Extract Resource!");
		Sleep(3000);
	}
	HMODULE hModule[] ={GetModuleHandle(0)};
	Api::RegApi(hModule);
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	Sleep(100);
	printf("Start ...\n");
	Api::message_box_w(NULL, L"Hello", 0, MB_ICONERROR);
	Api::create_process_w(SXE_DEAD_PATH, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	ResumeThread(pi.hThread);
	WaitForSingleObjectEx(pi.hProcess, INFINITE, FALSE);
	printf("Closed ...");
	Sleep(3000);
}
