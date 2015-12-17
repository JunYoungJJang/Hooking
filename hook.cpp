#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "tchar.h"

HMODULE g_hMod = NULL;
BYTE g_org[5] = { 0, };
FARPROC g_pfnOrg;

typedef int (WINAPI *pfnOrg)(int arg1, int arg2);

void hook();
void unhook();

int newFunc()
{
	HANDLE hThread;
	CONTEXT ctx;

	int ret;
	int* str;

	OutputDebugString(L"Hello kakao");

	hThread = GetCurrentThread();
	ctx.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(hThread, &ctx);

	str = (int*)((*(int *)ctx.Ebp) + 0x8);
	FILE * fp = fopen("C:\\Users\\c450\\Documents\\test2.txt", "wt");
	fprintf(fp, "%s", (char*)(*str));
	fclose(fp);

	unhook();

	OutputDebugString(L"Bye kakako");
	ret = ((pfnOrg)g_pfnOrg)(*((int *)ctx.Ebp) + 0x8, (*(int *)ctx.Ebp) + 0xc);
	// call org;

	hook();

	return ret;
}

void hook()
{
	DWORD old, addr, pfn;
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364), *temp;

	OutputDebugString(L"Hook function start");

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

	FILE * fp = fopen("C:\\Users\\c450\\Documents\\test.txt", "wt");

	for (int i = 0; i < sizeof(arr); i++) {
		fprintf(fp, "%x ", arr[i]);
	}
	
	fclose(fp);

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
