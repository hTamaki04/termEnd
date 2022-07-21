#include <stdio.h>
#define FALSE 0
#define TRUE 1

//�z��̒�����g���Ɠ���������B
int once[15][15];
int cntx, cnty;

int judgeOnce(int x, int y) {	//�R�}���u����Ă��邩�𒲂ׂ�B

	if (once[x][y] == 1 || once[x][y] == 2) {
		return FALSE;
	}
	return TRUE;
}

int judgeWeight(int x, int y, int user) {						//����5�ȏ㓯���F�̃R�}������ł��邩�𒲂ׂ�

	int mid = 1;
	int right = 0;
	int left = 0;
	
	 cntx = x;
	 cnty = y;

	while(1) {	//�E�����𒲂ׂ�
		if (once[++cntx][cnty] == user) {
			right++;
		}
		else {
			break;
		}
	}
	cntx -= (right + 1);

	while (1) {	//�������𒲂ׂ�
		if (once[--cntx][cnty] == user) {
			left++;
		}
		else {
			break;
		}
	}
	cntx += (left + 1);

	if ((right + left + mid) >= 5) {	//�܌ȏ㑵���Ώ���
		if (user == 1) {
			return 1;
		}
		else {
			return 2;
		}
	}

	return 0;
}

int judgeHeight(int x, int y, int user) {						//�c��5�ȏ㓯���F�̃R�}������ł��邩�𒲂ׂ�		

	int mid = 1;
	int up = 0;
	int down = 0;

	cntx = x;
	cnty = y;

	while (1) {	//������𒲂ׂ�
		if (once[cntx][--cnty] == user) {
			up++;
		}
		else {
			break;
		}
	}
	cnty += (up + 1);

	while (1) {	//�������𒲂ׂ�
		if (once[cntx][++cnty] == user) {
			down++;
		}
		else {
			break;
		}
	}
	cnty -= (down + 1);

	if ((up + down + mid) >= 5) {	//�܌ȏ㑵���Ώ���
		return user;
	}

	return 0;
}

int judgePositiveSlope(int x, int y, int user) {					//���̌X����5�ȏ㓯���F�̃R�}������ł��邩�𒲂ׂ�

	int mid = 1;
	int right = 0;
	int left = 0;

	cntx = x;
	cnty = y;

	while (1) {	//�E�����𒲂ׂ�
		if (once[++cntx][--cnty] == user) {
			right++;
		}
		else {
			break;
		}
	}

	cntx -= (right + 1);
	cnty += (right + 1);

	while (1) {	//�������𒲂ׂ�
		if (once[--cntx][++cnty] == user) {
			left++;
		}
		else {
			break;
		}
	}
	cnty += (left + 1);
	cnty -= (left + 1);

	if ((right + left + mid) >= 5) {	//�܌ȏ㑵���Ώ���
		return user;
	}

	return 0;
}

int judgeNegativeSlope(int x, int y, int user){					//���̌X����5�ȏ㓯���F�̃R�}������ł��邩�𒲂ׂ�

	int mid = 1;
	int right = 0;
	int left = 0;

	cntx = x;
	cnty = y;

	while (1) {	//�E�����𒲂ׂ�
		if (once[++cntx][++cnty] == user) {
			right++;
		}
		else {
			break;
		}
	}

	cntx -= (right + 1);
	cnty -= (right + 1);

	while (1) {	//�������𒲂ׂ�
		if (once[--cntx][--cnty] == user) {
			left++;
		}
		else {
			break;
		}
	}
	cnty += (left + 1);
	cnty += (left + 1);

	if ((right + left + mid) >= 5) {	//�܌ȏ㑵���Ώ���
		return user;
	}

	return 0;
}


