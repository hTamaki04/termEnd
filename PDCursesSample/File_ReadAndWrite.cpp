#include <stdio.h>
#include <Windows.h>

#define BUFFSIZE 1024

void writeFile(int player) {
	FILE* fp;
	errno_t error;

	int playerNum = player;

	error = fopen_s(&fp, "victoryPlayer.txt", "w");	//�t�@�C�����w�肷��B
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		fprintf(fp, "���҂�Player%d", playerNum);	//���������v���C���[���t�@�C���ɏ������ށB
		fclose(fp);
	}
}

int readFile(char* value) {

	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;
	char* p1;
	char delim[] = ", ";
	char* ctx;
	int height = 0;
	int length = 0;
	int data;

	error = fopen_s(&fp, value, "r");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			p1 = strtok_s(s, delim, &ctx); // 1�ڂ̕���������擾
			while (p1 != NULL) {
				if (height != 0) {
					data = atof(p1);
				}

				p1 = strtok_s(NULL, delim, &ctx); // 2�ڈȍ~�̕���������擾
				length++;
			}
			length = 0;
			height++;
		}
		fclose(fp);
	}
	return data;
}