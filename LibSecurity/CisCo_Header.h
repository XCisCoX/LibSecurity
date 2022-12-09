#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN            
#include <Windows.h>
#include <iostream>
#pragma warning (disable:4996)

namespace CISCO
{
	typedef struct tag_RegFunc {
		const char* name;
		FARPROC* ppfunc;
	} tRegFunc;
	class Api
	{
	public :
		//For reading in memory process
		static bool (WINAPI write_memory)(HANDLE hprocess, LPVOID address, LPCVOID data,SIZE_T size,SIZE_T*ret);
		static bool RegApi(HMODULE *hModule);
		static HMODULE(APIENTRY load_library_a)(char* lpFileName);
		static HMODULE(APIENTRY load_library_w)(wchar_t* lpFileName);
		static int (WINAPI
			message_box_w)(
				_In_opt_ HWND hWnd,
				_In_opt_ LPCWSTR lpText,
				_In_opt_ LPCWSTR lpCaption,
				_In_ UINT uType);
		static int
			(WINAPI 
			message_box_a)(
				_In_opt_ HWND hWnd,
				_In_opt_ LPCSTR lpText,
				_In_opt_ LPCSTR lpCaption,
				_In_ UINT uType);
		static	BOOL
			(WINAPI 
			create_process_a)(
				_In_opt_ LPCSTR lpApplicationName,
				_Inout_opt_ LPSTR lpCommandLine,
				_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
				_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
				_In_ BOOL bInheritHandles,
				_In_ DWORD dwCreationFlags,
				_In_opt_ LPVOID lpEnvironment,
				_In_opt_ LPCSTR lpCurrentDirectory,
				_In_ LPSTARTUPINFOA lpStartupInfo,
				_Out_ LPPROCESS_INFORMATION lpProcessInformation
			);
			static BOOL
			(WINAPI 
			create_process_w)(
				_In_opt_ LPCWSTR lpApplicationName,
				_Inout_opt_ LPWSTR lpCommandLine,
				_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
				_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
				_In_ BOOL bInheritHandles,
				_In_ DWORD dwCreationFlags,
				_In_opt_ LPVOID lpEnvironment,
				_In_opt_ LPCWSTR lpCurrentDirectory,
				_In_ LPSTARTUPINFOW lpStartupInfo,
				_Out_ LPPROCESS_INFORMATION lpProcessInformation
			);

	//For Writing in memory process
		static bool (WINAPI read_memory)(HANDLE hprocess, LPVOID address, LPCVOID data ,SIZE_T size,SIZE_T*ret);
	};
	class Process:Api
	{
	public:
		//For Killing A Process Name. 
		static bool kill(wchar_t*pName);
		/*For Check Are Current Application 
		Is run as admin or not*/
		static bool current_is_root();
		//For Blocking a API of dll in process
		static bool block_api(HANDLE hProcess, wchar_t*lib, char*api);
		//Get Another Handle Off dll Another Process
		static HMODULE get_handle_another();
		//Getting Process id from process name
		static bool get_process_id(wchar_t*pName);
	};

	class HardWare :Api
	{
	public:
		static std::string get_cpu_name();
	};

	class File :Api
	{
	public:
     /*
      Frist You Have To Add Your File In Resource
      Remember if You Have unknow type like
      executable file or any binary 
      set type ( RT_RCDATA ) and Set Name RCDATA
     */
	static bool extract_resource(wchar_t*szPath, int res_id, wchar_t* res_type);

	};
}