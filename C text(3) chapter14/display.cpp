#include"display.h"

#define ESCAPE_SEQUENCE 0

#if (ESCAPE_SEQUENCE == 0)
	#include<Windows.h>
#endif
void cls(){
#if (ESCAPE_SEQUENCE == 1)
	printf("\x1B[2J");
#else 
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdout != INVALID_HANDLE_VALUE) {
		static COORD				coordScreen;
		DWORD						dwCharsWritten;
		DWORD						dwConsoleXY;
		CONSOLE_SCREEN_BUFFER_INFO	csbi;
	
		if (GetConsoleScreenBufferInfo(hStdout, &csbi) == FALSE) return;

		dwConsoleXY = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(hStdout, ' ', dwConsoleXY, coordScreen, &dwCharsWritten);
		FillConsoleOutputAttribute(hStdout, csbi.wAttributes, dwConsoleXY, coordScreen, &dwCharsWritten);
		locate(1, 1);
	}
#endif
}

void locate(int x, int y) {
#if (ESCAPE_SEQUENCE == 1) printf("\x1B[%d;%dH", y, x);
#else 
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord{};

	if (hStdout != INVALID_HANDLE_VALUE) {
		coord.X = x - 1;
		coord.Y = y - 1;
		SetConsoleCursorPosition(hStdout, coord);
	}
#endif
}

void colorx(int fg, int bg) {
#if (ESCAPE_SEQUENCE == 1) 
	int col[] = { 31, 34, 31, 32, 35, 36, 33, 37 };
	printf("\x1B[0;");
	if (fg > WHILE) printf("1;");
	printf("%d;%dm", col[fig % 8], col[bg % 8] + 10);

#else 
	int col[] = { 0, 1, 4, 2, 5, 3, 6, 7, 8, 9, 12, 10, 13, 11, 14, 15 };
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attr = 0;

	if (hStdout == INVALID_HANDLE_VALUE) return;
	attr = (col[bg % 16] << 4) | col[fg % 16];
	SetConsoleTextAttribute(hStdout, attr);
#endif
}

void color(int col) {
	colorx(col, BLACK);
}
