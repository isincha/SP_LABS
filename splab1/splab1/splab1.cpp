#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#define BYTES_IN_MEGABYTE_NUMBER 1048576

void printLastErrorInfo();
void printHelpInfo();
void performErrorAndPrintInfo();
void printSystemInfo();

int main(int argc, char* argv[])
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc == 1) {
		printf("��� ����������\n");
		printHelpInfo();
		return 1;
	}

	if (!strcmp(argv[1], "-e")) {
		performErrorAndPrintInfo();
	}
	else if (!strcmp(argv[1], "-s")) {
		printSystemInfo();
	}
	else {
		printf("�������� ���������\n");
		printHelpInfo();
	}

	return 0;
}

void performErrorAndPrintInfo() {
	HANDLE handle = CreateFile(TEXT("Some\\error_path.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_NEW, 0, 0);
	if (handle == INVALID_HANDLE_VALUE) {
		printLastErrorInfo();
	}
	CloseHandle(handle);
}

void printLastErrorInfo() {
	LPVOID lpMsg;
	DWORD dwError;
	dwError = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsg, 0, NULL);
	wprintf(L"Error Code:  %lu\n", dwError);
	wprintf(L" Message: %s", lpMsg);
	LocalFree(lpMsg);
}

void printSystemInfo() {
	SYSTEM_INFO siSysInf;
	MEMORYSTATUS lpMemStat;

	GetSystemInfo(&siSysInf);
	printf("\n*** ��������� ���������� ***\n\n");
	printf("������ ��������: %u\n", siSysInf.dwPageSize);
	printf("����������� ����� ���������� : %u\n", siSysInf.lpMinimumApplicationAddress);
	printf("������������ ����� ���������� : %u\n", siSysInf.lpMaximumApplicationAddress);
	printf("�����, �������������� ����� �����������, ����������� � �������: %u\n", siSysInf.dwActiveProcessorMask);
	printf("���������� ���������� ����������� � ������� ������: %u\n", siSysInf.dwNumberOfProcessors);
	printf("������������� ������������� : %u\n", siSysInf.dwAllocationGranularity);
	printf("��� ����������� ����������: %u\n", siSysInf.wProcessorArchitecture);
	printf("������� ����������: %u\n", siSysInf.wProcessorLevel);
	printf("������� ����������: %u\n\n\n", siSysInf.wProcessorRevision);

	GlobalMemoryStatus(&lpMemStat);
	printf("*** ���������� � ������ ***\n\n");
	printf("������ ��������� ������ MemoryStatus: %ld b\n", lpMemStat.dwLength);
	printf("������������ ���������� ������ %ld%%.\n", lpMemStat.dwMemoryLoad);
	printf("���������� ������: %u MB\n", lpMemStat.dwTotalPhys / BYTES_IN_MEGABYTE_NUMBER);
	printf("��������� ���������� ������: %u MB\n", lpMemStat.dwAvailPhys / BYTES_IN_MEGABYTE_NUMBER);
	printf("������������ ����� ������ : %u MB\n", lpMemStat.dwTotalPageFile / BYTES_IN_MEGABYTE_NUMBER);
	printf("������������ ����� ������, ������� ����� ������������� ������� �������: %u MB\n", lpMemStat.dwAvailPageFile / BYTES_IN_MEGABYTE_NUMBER);
	printf("����������� ������: %u MB\n", lpMemStat.dwTotalVirtual / BYTES_IN_MEGABYTE_NUMBER);
	printf("��������� ����������� ������: %u MB\n", lpMemStat.dwAvailVirtual / BYTES_IN_MEGABYTE_NUMBER);
}

void printHelpInfo() {
	printf("\n����������� ��� ��������� :\n\n"
		"\t-e - ��������� �������� ������ � �������� ���������� �� ������\n"
		"\t-s - ����������� ���������� � �������\n\n");
}

