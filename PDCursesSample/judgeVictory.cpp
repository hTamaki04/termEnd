#include <stdio.h>
#define FALSE 0
#define TRUE 1

//配列の長さを枠数と等しくする。
int once[15][15];
int cntx, cnty;

int judgeOnce(int x, int y) {	//コマが置かれているかを調べる。

	if (once[x][y] == 1 || once[x][y] == 2) {
		return FALSE;
	}
	return TRUE;
}

int judgeWeight(int x, int y, int user) {						//横に5個以上同じ色のコマが並んでいるかを調べる

	int mid = 1;
	int right = 0;
	int left = 0;
	
	 cntx = x;
	 cnty = y;

	while(1) {	//右方向を調べる
		if (once[++cntx][cnty] == user) {
			right++;
		}
		else {
			break;
		}
	}
	cntx -= (right + 1);

	while (1) {	//左方向を調べる
		if (once[--cntx][cnty] == user) {
			left++;
		}
		else {
			break;
		}
	}
	cntx += (left + 1);

	if ((right + left + mid) >= 5) {	//五個以上揃えば勝ち
		if (user == 1) {
			return 1;
		}
		else {
			return 2;
		}
	}

	return 0;
}

int judgeHeight(int x, int y, int user) {						//縦に5個以上同じ色のコマが並んでいるかを調べる		

	int mid = 1;
	int up = 0;
	int down = 0;

	cntx = x;
	cnty = y;

	while (1) {	//上方向を調べる
		if (once[cntx][--cnty] == user) {
			up++;
		}
		else {
			break;
		}
	}
	cnty += (up + 1);

	while (1) {	//下方向を調べる
		if (once[cntx][++cnty] == user) {
			down++;
		}
		else {
			break;
		}
	}
	cnty -= (down + 1);

	if ((up + down + mid) >= 5) {	//五個以上揃えば勝ち
		return user;
	}

	return 0;
}

int judgePositiveSlope(int x, int y, int user) {					//正の傾きに5個以上同じ色のコマが並んでいるかを調べる

	int mid = 1;
	int right = 0;
	int left = 0;

	cntx = x;
	cnty = y;

	while (1) {	//右方向を調べる
		if (once[++cntx][--cnty] == user) {
			right++;
		}
		else {
			break;
		}
	}

	cntx -= (right + 1);
	cnty += (right + 1);

	while (1) {	//左方向を調べる
		if (once[--cntx][++cnty] == user) {
			left++;
		}
		else {
			break;
		}
	}
	cnty += (left + 1);
	cnty -= (left + 1);

	if ((right + left + mid) >= 5) {	//五個以上揃えば勝ち
		return user;
	}

	return 0;
}

int judgeNegativeSlope(int x, int y, int user){					//負の傾きに5個以上同じ色のコマが並んでいるかを調べる

	int mid = 1;
	int right = 0;
	int left = 0;

	cntx = x;
	cnty = y;

	while (1) {	//右方向を調べる
		if (once[++cntx][++cnty] == user) {
			right++;
		}
		else {
			break;
		}
	}

	cntx -= (right + 1);
	cnty -= (right + 1);

	while (1) {	//左方向を調べる
		if (once[--cntx][--cnty] == user) {
			left++;
		}
		else {
			break;
		}
	}
	cnty += (left + 1);
	cnty += (left + 1);

	if ((right + left + mid) >= 5) {	//五個以上揃えば勝ち
		return user;
	}

	return 0;
}


