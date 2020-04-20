#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>


#define BUFFER_SIZE 2048
#define MAX_FILE_NAME_SIZE 300
#define TEMP_FILE_NAME L"temp.txt"

using namespace std;

int main(int argc, char * argv[]);

void printHelpInfo();
void convertUnicodeToAsciiFile(HANDLE, HANDLE);
void convertAsciiToUnicodeFile(HANDLE, HANDLE);

int wmain(int argc, wchar_t* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc != 3) {
		printf("Неверное количество аргументов.\n");
		printHelpInfo();
		return 1;
	}

	const wchar_t* fileName = argv[2];
	wprintf(L"*** %s ***\n", fileName);

	HANDLE handleOriginalFile = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handleOriginalFile == INVALID_HANDLE_VALUE) {
		printf("ОШИБКА %x \n", GetLastError());
		return 2;
	}

	HANDLE handleNewFile = CreateFile(TEMP_FILE_NAME, GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handleNewFile == INVALID_HANDLE_VALUE) {
		printf("Temp file ОШИБКА %x \n", GetLastError());
		CloseHandle(handleOriginalFile);
		return 3;
	}

	if (!wcscmp(argv[1], L"-u")) {
		convertUnicodeToAsciiFile(handleOriginalFile, handleNewFile);
	}
	else if (!wcscmp(argv[1], L"-a")) {
		convertAsciiToUnicodeFile(handleOriginalFile, handleNewFile);
	}
	else {
		printf("Неверное значение аргумента ключа.\n");
		printHelpInfo();
		CloseHandle(handleOriginalFile);
		CloseHandle(handleNewFile);
		return 4;
	}

	wchar_t tempFileFullName[MAX_FILE_NAME_SIZE];
	GetFinalPathNameByHandle(handleNewFile, tempFileFullName, MAX_FILE_NAME_SIZE, FILE_NAME_OPENED);
	wchar_t originalFileFullName[MAX_FILE_NAME_SIZE];
	GetFinalPathNameByHandle(handleOriginalFile, originalFileFullName, MAX_FILE_NAME_SIZE, FILE_NAME_OPENED);

	CloseHandle(handleOriginalFile);
	CloseHandle(handleNewFile);

	BOOL moveResult = MoveFileEx(tempFileFullName, originalFileFullName, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
	if (!moveResult) {
		printf("Переименование ОШИБКИ %x \n", GetLastError());
		return 5;
	}

	return 0;
}

void convertUnicodeToAsciiFile(HANDLE handleFile, HANDLE handleNewFile) {
	printf("Конвертировать файл Unicode в Ascii\n\n");
	DWORD readBytesCount;
	DWORD writtenBytesCount;
	char asciiCharBytes[BUFFER_SIZE];
	wchar_t unicideBytes[BUFFER_SIZE];

	do {
		ReadFile(handleFile, unicideBytes, BUFFER_SIZE * 2, &readBytesCount, NULL);
		int encodedChars = WideCharToMultiByte(NULL, 0, unicideBytes, readBytesCount / 2, asciiCharBytes, BUFFER_SIZE, NULL, NULL);
		WriteFile(handleNewFile, asciiCharBytes, encodedChars, &writtenBytesCount, NULL);
	} while (readBytesCount >= BUFFER_SIZE && writtenBytesCount * 2 == readBytesCount);
}

void convertAsciiToUnicodeFile(HANDLE handleFile, HANDLE handleNewFile) {
	printf("Конвертировать Ascii файл в Unicode\n\n");
	DWORD readBytesCount;
	DWORD writtenBytesCount;
	char asciiCharBytes[BUFFER_SIZE];
	wchar_t unicideBytes[BUFFER_SIZE];

	do {
		ReadFile(handleFile, asciiCharBytes, BUFFER_SIZE, &readBytesCount, NULL);
		int encodedChars = MultiByteToWideChar(NULL, MB_COMPOSITE, asciiCharBytes, readBytesCount, unicideBytes, BUFFER_SIZE);
		WriteFile(handleNewFile, unicideBytes, encodedChars * 2, &writtenBytesCount, NULL);
	} while (readBytesCount >= BUFFER_SIZE && writtenBytesCount == readBytesCount * 2);
}

void printHelpInfo() {
	printf("Используйте <ключ> <имя файла> в качестве аргумента.\nключ:\n"
		"-u Unicode исходный файл\n"
		"-a ASCII исходный файл\n\n");
}

