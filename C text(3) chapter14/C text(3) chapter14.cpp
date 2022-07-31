#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

#define _1406


#ifdef _1401
enum {
	BLACK, BLUE, RED, GREEN, MAGENTA, CYAN, YELLOW, WHITE,
	GRAY, BRIGHT_BLUE, BRIGHT_RED, BRIGHT_GREEN,
	BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_YELLOW, BRIGHT_WHITE
};

void cls() {
	printf("\x1B[2J");
}

void locate(int x, int y) {
	printf("\x1B[%d;%dH", y, x);
}

void colorx(int fg, int bg) {
	int col[] = { 30, 34, 31, 32, 35, 36, 33, 37 };

	printf("\x1B[0;");
	if (fg > WHITE) printf("1;");
	printf("%d;%dm", col[fg % 8], col[bg % 8] + 10);
}

void color(int col) {
	colorx(col, BLACK);
}

int main(void) {
	cls();

	locate(3, 2); color(WHITE); printf("漢字");
	locate(3, 4); color(BLUE); printf("日本語");
	locate(3, 6); colorx(BLACK, BLUE); printf("いろはにほへと");
	locate(3, 8); colorx(BLUE, WHITE); printf("あいうえお");

	color(WHITE);

	return 0;
}
#endif

#ifdef _1405
#include "display.h"

const char* color_str[] = {
	"BLACK", "BLUE", "RED", "GREEN", "MAGENTA", "CYAN", "YELLOW", "WHITE",
	"GRAY", "BRIGHT_BLUE", "BRIGHT_RED", "BRIGHT_GREEN",
	"BRIGHT_MAGENTA", "BRIGHT_CYAN", "BRIGHT_YELLOW", "BRIGHT_WHITE"
};

int strcmpx(const char* s1, const char* s2) {
	while (toupper(*s1) == toupper(*s2)) {
		if (*s1 == '\0') return 0;
		s1++;
		s2++;
	}
	return toupper((unsigned char)*s1) - toupper((unsigned char)*s2);
}

int get_color(char* str) {
	for (int i = 0; i < sizeof(color_str) / sizeof(color_str[0]); i++) {
		if (!strcmpx(str, color_str[i])) return i;
	}
	return -1;
}

void error(int code) {
	switch (code) {
	case 1:
		fprintf(stderr, "文字色・背景色を指定してください。\n"); break;
		fprintf(stderr, "文字色の指定が正しくありません。\n"); break;
		fprintf(stderr, "背景色の指定が正しくありません。\n"); break;
	}
	fprintf(stderr, "---------------------------------------\n");
	fprintf(stderr, "SETCOLOR 文字色 [背景色]\n");
	fprintf(stderr, "---------------------------------------\n");
	fprintf(stderr, "文字色は以下に示す16色を、\n");
	fprintf(stderr, "背景色には左側の8色を指定してください。\n");
	fprintf(stderr, "背景色を省略すると黒とみなします。\n");
	fprintf(stderr, "---------------------------------------\n");
	fprintf(stderr, "BLACK			GRAY\n");
	fprintf(stderr, "BLUE			BRIGHT_BLUE\n");
	fprintf(stderr, "RED			BRIGHT_RED\n");
	fprintf(stderr, "GREEN			BRIGHT_GREEN\n");
	fprintf(stderr, "MAGENTA			BRIGHT_MAGENTA\n");
	fprintf(stderr, "CYAN			BRIGHT_CYAN\n");
	fprintf(stderr, "YELLOW			BRIGHT_YELLOW\n");
	fprintf(stderr, "WHITE			BRIGHT_WHITE\n");

	exit(1);
}

int main(int argc, char* argv[]) {
	int fg = 0;
	int bg = BLACK;
	if (argc < 2) error(1);
	if (argc >= 2) {
		if ((fg = get_color(argv[1])) == -1) error(2);
	}
	if (argc >= 3) {
		if ((bg = get_color(argv[2])) == -1) error(3);
	}
	colorx(fg, bg);

	return 0;
}
#endif

#ifdef _1406
#include<time.h>
#include"display.h"

int main(void) {
	int no = 0;
	int ans = 0;
	const int  max_stage = 10;
	int remain = max_stage;

	srand((unsigned)time(NULL));
	ans = rand() % 1000;

	printf("0～999の整数を当ててください。\n\n");

	do {
		color(BRIGHT_WHITE);
		printf("残り%d回。いくつかな : ", remain);
		scanf_s("%d", &no);
		remain--;

		if (no > ans) {
			color(BRIGHT_CYAN);
			printf("\aもっと小さいよ。\n");
		}
		else if (no < ans) {
			color(BRIGHT_GREEN);
			printf("\aもっと大きいよ。\n");
		}
	} while (no != ans && remain > 0);

	if (no != ans) {
		color(BRIGHT_RED);
		printf("\a残念。正解は%dでした。\n", ans);
	}
	else {
		color(BRIGHT_CYAN);
		printf("正解です。\n");
		printf("%d回で当たりましたね。\n", max_stage - remain);
	}

	color(WHITE);

	return 0;
}
#endif