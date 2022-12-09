#include"CisCo_Header.h"

namespace CISCO
{
#define C_CISCO_X OutputDebugStringW(L"-=(CISCO_X)=-");
#define OUT_DB(x) OutputDebugStringW(L##x);
#pragma region file_reg

	bool File::extract_resource(wchar_t*file_path,int resId,wchar_t* resType)
	{
		C_CISCO_X
		HRSRC hrsrc =
			FindResourceW(
				NULL,						//Module [ NULL = Current Module ]
				MAKEINTRESOURCEW(resId),	//Resource Id
				resType						//resource Type
			);

		if (!hrsrc)
		{
			OUT_DB("Can't Find Resource.")
			return false;
		}

		HGLOBAL handle_load = 
			LoadResource(
				NULL,	//Module [ NULL = Current Module ]
				hrsrc	//HRSRC of Resource
			);

		if (!handle_load) {
			OUT_DB("Can't Load Resource.")
			return false;
		}

		LPVOID lock_resource = 
		LockResource(
			handle_load //Loaded Handle of Resource
		);

		DWORD dw_size = 
		SizeofResource(
			NULL,
			hrsrc
		);
		HANDLE handle_file =
			CreateFileW(
				file_path,
				GENERIC_WRITE,
				NULL,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
		DWORD dw_byte_written;
		WriteFile(
				handle_file,
				lock_resource,
				dw_size,
				&dw_byte_written,
				NULL
			);
		if (dw_byte_written == NULL)
		{
			OUT_DB("Error In Writeing File!")
			return false;
		}
		CloseHandle(handle_file);
		FreeResource(handle_load);
		return true;
	}

#pragma endregion

#pragma region process_reg

	bool Process::block_api(HANDLE handle_process, wchar_t*library_name, char*library_api)
	{
		C_CISCO_X
			unsigned char byte_ret[] = { 0xC3 };
		HINSTANCE handle_lib = 0;
		void*full_address = 0;
		BOOL bool_return = false;
		DWORD dw_return = 0;
		handle_lib = LoadLibraryW(library_name);
		if (handle_lib)
		{
			full_address = (void*)GetProcAddress(
				handle_lib,
				library_api
			);
			write_memory(handle_process,
				(LPVOID)full_address,
				(LPCVOID)byte_ret,
				sizeof(byte_ret),
				&dw_return);
			if (!dw_return)
			{
				bool_return = false;
			}
			FreeLibrary(handle_lib);
		}
		return bool_return;
	}
	bool Process::current_is_root()
	{
		C_CISCO_X
		BOOL fRet = FALSE;
		HANDLE hToken = NULL;
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
			TOKEN_ELEVATION Elevation;
			DWORD cbSize = sizeof(TOKEN_ELEVATION);
			if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
				fRet = Elevation.TokenIsElevated;
			}
		}
		if (hToken) {
			CloseHandle(hToken);
		}
		return fRet;
	}
	bool Process::get_process_id(wchar_t*process_name)
	{
		C_CISCO_X

	}
	bool Process::kill(wchar_t*process_name)
	{
		C_CISCO_X

	}

	bool _InitAPI(tRegFunc* aFuncs, int Count, const wchar_t* chLibName, HMODULE* hLib, bool UsePostfix)
	{
		int i;
		if (!hLib) return false;
		*hLib = LoadLibrary(chLibName);
		if (!*hLib)
			return false;
		for (i = 0; i < Count; i++)
		{
			char sFuncName[0x100];
			FARPROC pFunc;
			strcpy(sFuncName, ((*(tRegFunc*)((DWORD)aFuncs + sizeof(tRegFunc)*i))).name);
			pFunc = GetProcAddress(*hLib, sFuncName);
			if (pFunc == NULL)
				return false;
			*((*(tRegFunc*)((DWORD)aFuncs + sizeof(tRegFunc)*i))).ppfunc = pFunc;
		}
		return true;
	}

	bool Api::RegApi(HMODULE *hModule)
	{
		tRegFunc	aRegFuncs_User32[] = {
		{"MessageBoxA",(FARPROC*)&message_box_a},
		{"MessageBoxW",(FARPROC*)&message_box_w} 
		};

		tRegFunc	aRegFuncs_Kernel32[] = {
		{"CreateProcessA",(FARPROC*)&create_process_a},
		{"CreateProcessW",(FARPROC*)&create_process_w},
		{"WriteProcessMemory",(FARPROC*)&write_memory},
		{"ReadProcessMemory",(FARPROC*)&read_memory},
		{"LoadLibraryA",(FARPROC*)&load_library_a},
		{"LoadLibraryA",(FARPROC*)&load_library_w},
		};

		return ((_InitAPI(aRegFuncs_User32,
		sizeof(aRegFuncs_User32),
		__TEXT("user32.dll"), 
		hModule, 
		true)
		&&
		_InitAPI(aRegFuncs_Kernel32,
		sizeof(aRegFuncs_Kernel32),
		__TEXT("kernel32.dll"),
		hModule, 
		true))?
		true:false);
	}
	
	bool Api::read_memory(HANDLE hprocess, LPVOID address, LPCVOID data, SIZE_T size, SIZE_T*ret)
	{
		C_CISCO_X

	}
	bool Api::write_memory(HANDLE hprocess, LPVOID address, LPCVOID data, SIZE_T size, SIZE_T*ret)
	{
		C_CISCO_X

	}
	HMODULE Process::get_handle_another()
	{
		C_CISCO_X

	}

#pragma endregion

#pragma region hardware_reg
	std::string HardWare::get_cpu_name()
	{
		C_CISCO_X

	}


#pragma endregion

}