// splab0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

int main()
{
	INT int_min = 0xFFFFFFFF80000000;
	INT int_max = 0x7FFFFFFF;
	LONG long_min = 0xFFFFFFFF80000000;
	LONG long_max = 0x7FFFFFFF;
	SHORT short_min = 0xFFFFFFFFFFFF8001;
	SHORT short_max = 0x7FFF;
	BYTE byte_min = 0x0;
	BYTE byte_max = 0xFF;
	UINT uint_min = 0x0;
	UINT uint_max = 0xFFFFFFFF;
	ULONG ulong_min = 0x0;
	ULONG ulong_max = 0xFFFFFFFF;
	WORD word_min = 0x0;
	WORD word_max = 0xFFFF;
	DWORD dword_min = 0x0;
	DWORD dword_max = 0xFFFFFFFF;
	int char_min = 0x0;
	int char_max = 0xFF;

	printf("+---------+-------+-----------+-----------+\n");
	printf("|Data type|size of|    Min    |    Max    |\n");
	printf("+---------+-------+-----------+-----------+\n");
	printf("|INT      |  %dB   |%11i|%11i|\n", sizeof(INT), int_min, int_max);
	printf("|LONG     |  %dB   |%11d|%11d|\n", sizeof(LONG), long_min, long_max);
	printf("|SHORT    |  %dB   |%11d|%11d|\n", sizeof(SHORT), short_min, short_max);
	printf("|BYTE     |  %dB   |%11d|%11d|\n", sizeof(BYTE), byte_min, byte_max);
	printf("+---------+-------+-----------+-----------+\n");
	printf("|UINT     |  %dB   |%11d|%11u|\n", sizeof(UINT), uint_min, uint_max);
	printf("|ULONG    |  %dB   |%11d|%11u|\n", sizeof(ULONG), ulong_min, ulong_max);
	printf("+---------+-------+-----------+-----------+\n");
	printf("|WORD     |  %dB   |%11d|%11d|\n", sizeof(WORD), word_min, word_max);
	printf("|DWORD    |  %dB   |%11d|%11u|\n", sizeof(DWORD), dword_min, dword_max);
	printf("+---------+-------+-----------+-----------+\n");
	printf("|BOOL     |  %dB   |\n", sizeof(BOOL));
	printf("|BOOLEAN  |  %dB   |\n", sizeof(BOOLEAN));
	printf("+---------+-------+\n");
	printf("|CHAR     |  %dB   |\n", sizeof(CHAR));
	printf("|WCHAR    |  %dB   |\n", sizeof(WCHAR));
	printf("|TCHAR    |  %dB   |\n", sizeof(TCHAR));
	printf("+---------+-------+\n");
	printf("|LPSTR    |  %dB   |\n", sizeof(LPSTR));
	printf("|LPCSTR   |  %dB   |\n", sizeof(LPCSTR));
	printf("|LPWSTR   |  %dB   |\n", sizeof(LPWSTR));
	printf("|LPCWSTR  |  %dB   |\n", sizeof(LPCWSTR));
	printf("|LPTSTR   |  %dB   |\n", sizeof(LPTSTR));
	printf("|LPCTSTR  |  %dB   |\n", sizeof(LPCTSTR));
	printf("+---------+-------+\n");
	printf("|HANDLE   |  %dB   |\n", sizeof(HANDLE));
	printf("|HLOCAL   |  %dB   |\n", sizeof(HLOCAL));
	printf("|HINSTANCE|  %dB   |\n", sizeof(HINSTANCE));
	printf("|HMENU    |  %dB   |\n", sizeof(HMENU));
	printf("+---------+-------+\n");
}

