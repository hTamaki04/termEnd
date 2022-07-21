#include <stdio.h>
#include <Windows.h>
#include <curses.h>
#include <stdlib.h>
#include "gameSetting.h"
#include "judgeVictory.h"

BOOL changeConsoleSize(int x, int y) { //�R���\�[���T�C�Y��ύX����B
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

	// Step1. ��x�R���\�[���\���T�C�Y��������Ə���������
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);

	// Step2. �o�b�t�@�T�C�Y��ړI�̑傫���ɐݒ肷��
	if (!SetConsoleScreenBufferSize(hStdout, coord)) {
		return FALSE;
	}

	// Step3. �E�B���h�E�T�C�Y��ړI�̑傫���ɐݒ�ɂ���
	rectConsoleSize.Right = x - 1;
	rectConsoleSize.Bottom = y - 1;
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
	return TRUE;
}

void fieldSetting() {
	int i,j;

	// ��ʂ��N���A
	erase();

	mvaddstr(1, 90, "[�ܖڕ���]");
	mvaddstr(2, 90, "�E���{�^���ŃJ�[�\�����ړ�����");
	mvaddstr(3, 90, "�Ea�{�^���ŃR�}��u��");

	//�R�}�̔z�u������������B
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			once[i][j] = 0;
		}
	}

	//�t�B�[���h��ݒ肷��B
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
		attrset(COLOR_PAIR(1));			// �F�P���f�t�H���g�F�Ƃ���
		mvprintw(10, 90, "Player %d WIN!!", player);
		mvprintw(12, 90, "r�{�^���Ń��g���C");
		key = getch();
		if (key == 'r') {
			fieldSetting();	//�t�B�[���h��ݒ肷��B
			break;
		}
	}
}
