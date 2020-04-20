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
		printf("Без аргументов\n");
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
		printf("Неверные аргументы\n");
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
	printf("\n*** Системная информация ***\n\n");
	printf("Размер страницы: %u\n", siSysInf.dwPageSize);
	printf("Минимальный адрес приложения : %u\n", siSysInf.lpMinimumApplicationAddress);
	printf("Максимальный адрес приложения : %u\n", siSysInf.lpMaximumApplicationAddress);
	printf("Маска, представляющая набор процессоров, настроенных в системе: %u\n", siSysInf.dwActiveProcessorMask);
	printf("Количество логических процессоров в текущей группе: %u\n", siSysInf.dwNumberOfProcessors);
	printf("Гранулярность распределения : %u\n", siSysInf.dwAllocationGranularity);
	printf("Код архитектуры процессора: %u\n", siSysInf.wProcessorArchitecture);
	printf("Уровень процессора: %u\n", siSysInf.wProcessorLevel);
	printf("Ревизия процессора: %u\n\n\n", siSysInf.wProcessorRevision);

	GlobalMemoryStatus(&lpMemStat);
	printf("*** Информация о памяти ***\n\n");
	printf("Размер структуры данных MemoryStatus: %ld b\n", lpMemStat.dwLength);
	printf("Используемая физическая память %ld%%.\n", lpMemStat.dwMemoryLoad);
	printf("Физическая память: %u MB\n", lpMemStat.dwTotalPhys / BYTES_IN_MEGABYTE_NUMBER);
	printf("Свободная физическая память: %u MB\n", lpMemStat.dwAvailPhys / BYTES_IN_MEGABYTE_NUMBER);
	printf("Ограниченный объем памяти : %u MB\n", lpMemStat.dwTotalPageFile / BYTES_IN_MEGABYTE_NUMBER);
	printf("Максимальный объем памяти, который может зафиксировать текущий процесс: %u MB\n", lpMemStat.dwAvailPageFile / BYTES_IN_MEGABYTE_NUMBER);
	printf("Виртуальная память: %u MB\n", lpMemStat.dwTotalVirtual / BYTES_IN_MEGABYTE_NUMBER);
	printf("Свободная виртуальная память: %u MB\n", lpMemStat.dwAvailVirtual / BYTES_IN_MEGABYTE_NUMBER);
}

void printHelpInfo() {
	printf("\nИспользуйте это аргументы :\n\n"
		"\t-e - выполнить операцию ошибки и получить информацию об ошибке\n"
		"\t-s - распечатать информацию о системе\n\n");
}

