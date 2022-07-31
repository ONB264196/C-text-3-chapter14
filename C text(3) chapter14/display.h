#pragma once
enum {
	BLACK,
	BLUE,
	RED,
	GREEN,
	MAGENTA,
	CYAN,
	YELLOW,
	WHITE,
	GRAY,
	BRIGHT_BLUE,
	BRIGHT_RED,
	BRIGHT_GREEN,
	BRIGHT_MAGENTA,
	BRIGHT_CYAN,
	BRIGHT_YELLOW,
	BRIGHT_WHITE
};

void cls();

void locate(int __x, int __y);

void colorx(int __fg, int __bg);

void color(int __col);