#pragma once
#define FIELD_LEFT 20
#define FIELD_RIGHT 80
#define FIELD_UP 0
#define FIELD_DOWN 30

BOOL changeConsoleSize(int x, int y);
void fieldSetting();
void endSetting(int player);
void locate(unsigned char x, unsigned char y);
