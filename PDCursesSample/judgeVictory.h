#pragma once
//配列の長さを枠数と等しくする。
extern int once[15][15];

int judgeOnce(int x, int y);
int judgeWeight(int x, int y, int user);
int judgeHeight(int x, int y, int user);
int judgePositiveSlope(int x, int y, int user);
int judgeNegativeSlope(int x, int y, int user);
