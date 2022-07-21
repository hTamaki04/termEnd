
#include <stdio.h>
#include <Windows.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "judgeVictory.h"
#include "gameSetting.h"
#include "file_ReadAndWrite.h"

#define CHARBUFF 124

void locate(unsigned char x, unsigned char y);
void getGurrentDirectory(char* currentDirectory);
int judgeOnce(int x, int y);
void writeFile(int player);
int readFile(char* value);

typedef struct {	//プレイヤーの場所を示す
	unsigned short x;
	unsigned short y;
}point;
point p;

int i = 0;	//for文で利用する。
int j = 0;	//for文で利用する。
int playerNum = 0; //ユーザ番号

int main(int argc, char* argv[])
{
	changeConsoleSize(140, 35);	//コンソールサイズを変更する。
	char num[12];	//数字を文字に変換する際に用いる変数。
	int timeLimit;

	//iniファイル読み込み
	char currentDirectory[CHARBUFF];		//取得した現在のディレクトリ名を格納
	getGurrentDirectory(currentDirectory);	//現在のディレクトリを取得
	char section[CHARBUFF];
	sprintf_s(section, "section1");
	char keyWord[CHARBUFF];
	sprintf_s(keyWord, "time");
	char settingFile[CHARBUFF];	//取得した初期化ファイルの絶対パスを格納
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);	//現在のディレクトリ+ファイル名で，初期化ファイルの絶対パスを作成
	char keyValue[CHARBUFF];
	if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile) != 0) {
		timeLimit = readFile(keyValue);
	}
	else {
		fprintf(stdout, "%s doesn't contain [$s] %s\n", settingFile, section, keyWord);
	}

	time_t start_time, end_time; //プレイヤーのターンの始まり時間と終わり時間

	// 初期化
	if (initscr() == NULL) {
		return 1;
	}

	start_color();	// カラーの設定
	init_pair(1, COLOR_WHITE, COLOR_BLUE);		// 色番号１を白文字／青地とする
	init_pair(2, COLOR_BLUE, COLOR_WHITE);		// 色番号１を青文字／白地とする
	init_pair(3, COLOR_YELLOW, COLOR_BLUE);		// 色番号１を黄文字／白地とする
	init_pair(4, COLOR_GREEN, COLOR_BLUE);		// 色番号１を緑文字／白地とする
	bkgd(COLOR_PAIR(1));						// 色１をデフォルト色とする

	//フィールド設定
	fieldSetting();

	//特殊キー可能にする
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	//ユーザ1の初期設定
	int x = 12;
	int y = 8;
	locate(x, y);
	attrset(COLOR_PAIR(3));
	mvaddstr(p.y, p.x, "-----");
	timeout(1);
	// 処理開始前の時間を取得 
	start_time = time(NULL);

	while (true) {
		int key = getch();	//キーボタン取得
		if (key == 'a') {
			if (judgeOnce(x - FIELD_LEFT / 4, y) == TRUE) { //コマが置いてなかった場合
				if (playerNum % 2 == 0) {		//ユーザ1
					attrset(COLOR_PAIR(3));		//黄文字に設定
					mvaddstr(p.y - 1, p.x + 1, "■");
					once[x - FIELD_LEFT / 4][y] = 1;	//ユーザ1のコマを記憶する
				}
				else if (playerNum % 2 == 1) {	//ユーザ2
					attrset(COLOR_PAIR(4));		//緑色に設定
					mvaddstr(p.y - 1, p.x + 1, "■");
					once[x - FIELD_LEFT / 4][y] = 2;	//ユーザ2のコマを記憶する
				}

				//五個同じ色のコマが連続しているのかを調べる
				if ((judgeWeight((x - FIELD_LEFT / 4), y, playerNum % 2 + 1) == (playerNum % 2) + 1)|| 
					(judgeHeight((x - FIELD_LEFT / 4), y, playerNum % 2 + 1) == (playerNum % 2) + 1)||
					(judgePositiveSlope((x - FIELD_LEFT / 4), y, playerNum % 2 + 1) == (playerNum % 2) + 1) ||
					(judgeNegativeSlope((x - FIELD_LEFT / 4), y, playerNum % 2 + 1) == (playerNum % 2) + 1) ) {
							
					writeFile((playerNum % 2) + 1);	 //結果をファイルに書き込む
					endSetting((playerNum % 2) + 1); //試合終了
					playerNum = 1;	//プレイヤー1からスタートする
					
				}
				playerNum++; //次のプレイヤーに変更
				start_time = time(NULL);	//ターン開始時の時間を取得
			}
		}

		end_time = time(NULL);	//現在の時間を取得

		attrset(COLOR_PAIR(1));	//白文字に設定
		//iniファイルで設定した時間を経過すると敗北する
		if ((end_time - start_time) > timeLimit) {
			if (playerNum % 2 == 0) {	//プレイヤー1
				writeFile(2);	//勝利結果をファイルに書き込む
				endSetting(2);	//試合終了
			}
			else if (playerNum % 2 == 1) {	//プレイヤー1
				writeFile(1);	//勝利結果をファイルに書き込む
				endSetting(1);	//試合終了
			}
			start_time = time(NULL);	//ターン開始時間を更新
			end_time = time(NULL);		//現在時間を更新
			playerNum = 0; 	//プレイヤー1からスタートする
		}
		else {
			//残り時間を文字に変更
			snprintf(num, 12, "%d", timeLimit - (end_time - start_time));
			mvaddstr(5, 90, "残り時間：");
			mvaddstr(5, 100, "   "); //時間部分を消す
			mvaddstr(5, 100, num);	 //残り時間表示
		}

		//矢印ボタンを押すと現在のカーソル部分を白色に戻す。
		if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP || key == KEY_DOWN) {
			attrset(COLOR_PAIR(1));
			mvaddstr(p.y, p.x, "-----");

		}

		//矢印ボタンによってカーソルを移動する
		if (key == KEY_RIGHT) {
			if (p.x < FIELD_RIGHT - 4 ) { //フィールド範囲を超えないようにする。
				locate(++x, y);
			}
		}
		else if (key == KEY_LEFT) {
			if (p.x > FIELD_LEFT) {
				locate(--x, y);
			}
		}
		else if (key == KEY_UP) {
			if (p.y > FIELD_UP) {
				locate(x, --y);
			}
		}
		else if (key == KEY_DOWN) {
			if (p.y < FIELD_DOWN) {
				locate(x, ++y);
			}
		}

		//プレイヤーによって色を変える
		if (playerNum % 2 == 0) {
			attrset(COLOR_PAIR(3));
			mvaddstr(p.y, p.x, "-----");
		}
		else if (playerNum % 2 == 1) {
			attrset(COLOR_PAIR(4));
			mvaddstr(p.y, p.x, "-----");
		}

		// 画面を更新
		refresh();
	}

	while(1);
	return 0;
}

void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);	//現在のディレクトリを取得
}

void locate(unsigned char x, unsigned char y) {		//位置の指定
	p.x = x * 4;
	p.y = y * 2;
}

