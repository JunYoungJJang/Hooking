#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>

DWORD GetPIDByName(LPCTSTR szProcessName)
{
	DWORD PID = 0xFFFFFFFF;
	HANDLE hSnapShot = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe;
	char proc_name[260];

	pe.dwSize = sizeof(PROCESSENTRY32);
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	Process32First(hSnapShot, &pe);
	do
	{
		strncpy(proc_name, pe.szExeFile, strlen(pe.szExeFile));
		if (!_strnicmp(szProcessName, proc_name, strlen(szProcessName)))
		{
			// 현재 프로세스 목록 중 target 프로세스의 이름과 같은 것이 있으면
			// PID를 반환 
			PID = pe.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnapShot, &pe));
	CloseHandle(hSnapShot);
	return PID;
}

DWORD GetModuleBaseAddrByPID(int pid)
{
	HANDLE hSnapshot;
	MODULEENTRY32 me32;
	DWORD dwAddress = 0xFFFFFFFF;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

	if (!hSnapshot)
		return FALSE;

	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hSnapshot, &me32))
		return FALSE;

	do {
		if (me32.th32ProcessID == pid)
		{
			// target 프로세스에서 프로그램의 base 주소를 구함 
			// 하나의 프로세스에는 (Dll 등) 여러 모듈이 있어서
			// 그 중에서 target 프로세스와 pid가 같은 모듈이
			// 실제 우리가 실행시킨 프로그램의 코드가 있는 위치임 
			dwAddress = me32.modBaseAddr;
			break;
		}
	} while (Module32Next(hSnapshot, &me32));
	return dwAddress;
}

void main()
{
	DWORD old, BaseAddr, Read, TargetAddr;
	BYTE ReadBytes[20], MulAddr[4];
	int pid = GetPIDByName("target");
	printf(" PID : %d\n", pid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	BaseAddr = GetModuleBaseAddrByPID(pid);
	printf(" BaseAddr : %#x \n", BaseAddr);

	if (!hProcess)
	{
		printf("Error : %d", GetLastError());
		exit(0);
	}
	
	TargetAddr = BaseAddr + 0x132C;
	
	ReadProcessMemory(hProcess, TargetAddr, &ReadBytes, 5 ,&Read);
	printf(" OPCODE : %x \n", ReadBytes[0]); // E8
	// OPCode E8은 CAll 명령어임 
	
	MulAddr[0] = 0xAE;
	MulAddr[1] = 0xFF;
	MulAddr[2] = 0xFF;
	MulAddr[3] = 0xFF; 
	
	VirtualProtectEx(hProcess, (LPVOID)TargetAddr, 1, PAGE_EXECUTE_READWRITE, &old);
	WriteProcessMemory(hProcess, (LPVOID)TargetAddr+1, (LPVOID)MulAddr, 1, &old);
	
}
