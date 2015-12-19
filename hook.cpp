#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "tchar.h"
#include "Shlobj.h"

HMODULE g_hMod = NULL;
BYTE g_org[5] = { 0, };
FARPROC g_pfnOrg;
char path[MAX_PATH] = { 0, };

typedef int (WINAPI *pfnOrg)(int arg1, int arg2);

void hook();
void unhook();

void newFunc(char* arg1, LPVOID arg2)
{
	HANDLE hThread;
	CONTEXT ctx;

	int* ret;
	char* str;

	__asm pushad;   // pushad

	OutputDebugString(L"Hello kakao");

	hThread = GetCurrentThread();
	ctx.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(hThread, &ctx);

	str = arg1;
	FILE * fp = fopen(strcat(path, "\\Documents\\test.txt"), "wt");
	fprintf(fp, "%s", str);
	fclose(fp);

	OutputDebugString(L"Bye kakao");

	unhook();

	ret = (int *) (*((int *)ctx.Ebp + 2) + 0x4);   // ebp + 0x4
	*ret = *ret - 5;

	__asm popad;   // popad
}

void hook()
{
	DWORD old, addr, pfn;
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364), *temp;

	OutputDebugString(L"Hook function start");

	if (g_org[0]) {   // already hooked!
		return;
	}

	pfn = *((DWORD*)(ptr + 1)) + 5 + (0x400000 + 0x33A364);
	g_pfnOrg = (FARPROC)pfn;

	for (int i = 0; i < 5; i++) {
		g_org[i] = *ptr++;
	}
	ptr = (BYTE*)(0x400000 + 0x33A364 + 1);

	VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &old);

	addr = (DWORD)newFunc - (0x400000 + 0x33A364) - 5;
	temp = (BYTE*)&addr;

	for (int i = 0; i < 4; i++) {
		*ptr++ = *temp++;
	}

	VirtualProtect(ptr, 5, old, NULL);

	OutputDebugString(L"Hook function end");
}

void unhook()
{
	DWORD old;
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364);

	VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &old);

	for (int i = 0; i < 5; i++) {
		*ptr++ = g_org[i];
	}

	VirtualProtect(ptr, 5, old, NULL);
}

DWORD WINAPI ThreadProc(LPVOID lParam)
{
	BYTE arr[5];
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364);

	for (int i = 0; i < sizeof(arr); i++) {
		arr[i++] = *ptr++;
	}

	SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path);

	hook();

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	HANDLE hThread = NULL;

	g_hMod = (HMODULE)hinstDLL;

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"<hook.dll> Injection!!!");
		hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		CloseHandle(hThread);
		break;
	}

	return TRUE;
}
