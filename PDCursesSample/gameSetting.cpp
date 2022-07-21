#include <stdio.h>
#include <Windows.h>
#include <curses.h>
#include <stdlib.h>
#include "gameSetting.h"
#include "judgeVictory.h"

BOOL changeConsoleSize(int x, int y) { //コンソールサイズを変更する。
	HANDLE hStdout;
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SMALL_RECT rectConsoleSize;
	rectConsoleSize.Left = 0;
	rectConsoleSize.Top = 0;
	rectConsoleSize.Right = 1;
	rectConsoleSize.Bottom = 1;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Step1. 一度コンソール表示サイズをぎゅっと小さくする
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);

	// Step2. バッファサイズを目的の大きさに設定する
	if (!SetConsoleScreenBufferSize(hStdout, coord)) {
		return FALSE;
	}

	// Step3. ウィンドウサイズを目的の大きさに設定にする
	rectConsoleSize.Right = x - 1;
	rectConsoleSize.Bottom = y - 1;
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
	return TRUE;
}

void fieldSetting() {
	int i,j;

	// 画面をクリア
	erase();

	mvaddstr(1, 90, "[五目並べ]");
	mvaddstr(2, 90, "・矢印ボタンでカーソルを移動する");
	mvaddstr(3, 90, "・aボタンでコマを置く");

	//コマの配置を初期化する。
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			once[i][j] = 0;
		}
	}

	//フィールドを設定する。
	for (i = FIELD_UP; i <= FIELD_DOWN; i++) {
		for (j = FIELD_LEFT; j <= FIELD_RIGHT; j++) {
			if ((i % 2) == 0) {
				mvaddstr(i, j, "-");
			}
			else if ((j % 4) == 0) {
				mvaddstr(i, j, "|");
			}
		}
	}
}

void endSetting(int player) {
	int key;
	while (1) {
		attrset(COLOR_PAIR(1));			// 色１をデフォルト色とする
		mvprintw(10, 90, "Player %d WIN!!", player);
		mvprintw(12, 90, "rボタンでリトライ");
		key = getch();
		if (key == 'r') {
			fieldSetting();	//フィールドを設定する。
			break;
		}
	}
}
