#include "SZQ_basic.h"
#include<Arduino.h>
/*
* @brief    creat  chequer
*/
char** creatQP() {
	char** QP;
	QP = (char**)malloc(sizeof(char*) * N);
	int i = 0;
	if (QP == NULL)
		return NULL;
	for (i = 0; i < N; i++) {
		QP[i] = (char*)malloc(sizeof(char) *N);
		if (QP[i] == NULL)
			return NULL;
		memset(QP[i], ' ', sizeof(char)*N);
	}
	return QP;
}

/*
* @brief    Serial.printf Chequer
* @para     棋盘地址
*/
void printQP(char** QP) {
	int i = 0,j = 0,k = 0;
	if (QP == NULL) {
		Serial.printf("print Chequer failed!");
		return;
	}

	Serial.printf("|_____________________________    棋盘    ___________________________|\n");
	Serial.printf("\t\t 行号→  1   2   3\t\t玩家棋子：“o”\n\t\t 列号↓\t\t\t\t电脑棋子：“X”\n");
	Serial.printf("\t\t       |---|---|---|\n");
	for (i = 0; i < N; i++) {
		Serial.printf("\t\t      %d|", i + 1);
		for (j = 0; j < N; j++) {
			Serial.printf(" %c |", QP[i][j]);
		}
		Serial.printf("\n");
		Serial.printf("\t\t       |");
		for (j = 0; j < N; j++) {
			Serial.printf("---|");
		}
		Serial.printf("\n");
	}
	Serial.printf("|--------------------------------------------------------------------|\n");
}


int inputQZ(char** QP, int row, int column) {
	if (row < 0 || row>2 || column < 0 || column>2) {
		Serial.printf("输入棋子位置不合法！\n请重新输入：>>");
		return 0;
	}
	if (QP[row][column] != ' ') {
		Serial.printf("该位置已有棋子！\n请重新输入：>>");
		return 0;
	}
	QP[row][column] = P_pawn;
	return 1;
}


/*
* brief  判断棋盘是否满了，满了即平局
*/
int isQPFull(char** QP) {
	int i = 0,j = 0,k = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (QP[i][j] ==' ')
				return 0;
		}
	}
	return 1;
}


/*
*@brief  判断游戏是否结束（玩家获胜？）
*@ret    1:玩家胜   0：游戏未结束   -1：玩家败
*/
int isPlayerWin(char** QP) {
	int flag = 0;
	int i = 0,j = 0,k = 0;

	//判断行成线
	for (i = 0; i < N; i++)
	{
		if (QP[i][0] == QP[i][1] && QP[i][0] == QP[i][2] && QP[i][0] == C_pawn)
			flag = -1;
		else if (QP[i][0] == QP[i][1] && QP[i][0] == QP[i][2] && QP[i][0] == P_pawn)
			flag = 1;
	}
	//判断列成线
	for (j = 0; j < N; j++)
	{
		if (QP[0][j] == QP[1][j] && QP[0][j] == QP[2][j] && QP[0][j] == C_pawn)
			flag = -1;
		else if (QP[0][j] == QP[1][j] && QP[0][j] == QP[2][j] && QP[0][j] == P_pawn)
			flag = 1;
	}
	//判断正对角成线
	if (QP[0][0] == QP[1][1] && QP[0][0] == QP[2][2] && QP[0][0] == C_pawn)
		flag = -1;
	else if (QP[0][0] == QP[1][1] && QP[0][0] == QP[2][2] && QP[0][0] == P_pawn)
		flag = 1;

	//判断反对角成线
	if (QP[0][2] == QP[1][1] && QP[0][2] == QP[2][0] && QP[0][2] == C_pawn)
		flag = -1;
	else if (QP[0][2] == QP[1][1] && QP[0][2] == QP[2][0] && QP[0][2] == P_pawn)
		flag = 1;

	return flag;
}



