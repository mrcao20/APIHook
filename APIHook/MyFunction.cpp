#include "stdafx.h"
#include "MyFunction.h"

extern vector<FARPROC> pOldFuncs;

size_t indexFind(string value);
void HookOn(size_t index);
void HookOff(size_t index);
void WriteToFile(const char *str);

typedef HANDLE(WINAPI *CreateFileWProc)(LPCWSTR               lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile);

HANDLE WINAPI MyCreateFileW(LPCWSTR               lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile) {

	string funcName = "CreateFileW";
	size_t index = indexFind(funcName);
	CreateFileWProc oldFunc = (CreateFileWProc)pOldFuncs.at(index);
	HookOff(index);//�ص�Myadd()���ӷ�ֹ��ѭ��
	WriteToFile("has been the hooks��CreateFileW");
	HANDLE dwRetVal;
	dwRetVal = oldFunc(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	HookOn(index);//����Myadd()����
	return dwRetVal;
}

typedef BOOL(WINAPI *WriteFileWProc)(HANDLE       hFile,
	LPCVOID      lpBuffer,
	DWORD        nNumberOfBytesToWrite,
	LPDWORD      lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped);

BOOL WINAPI MyWriteFile(HANDLE       hFile,
	LPCVOID      lpBuffer,
	DWORD        nNumberOfBytesToWrite,
	LPDWORD      lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped) {

	string funcName = "WriteFile";
	size_t index = indexFind(funcName);
	WriteFileWProc oldFunc = (WriteFileWProc)pOldFuncs.at(index);
	HookOff(index);//�ص�Myadd()���ӷ�ֹ��ѭ��
	WriteToFile("has been the hooks��WriteFile");
	BOOL dwRetVal;
	dwRetVal = oldFunc(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	HookOn(index);//����Myadd()����
	return dwRetVal;
}