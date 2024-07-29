#include "SZQ_basic.h"
#include "SZQ_engine.h"




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  	int hang, lie;
	int cmd = 1;
	int position;
	int i = 0,j = 0,k = 0;
	char** TicTacToe = creatQP();
	Serial.printf("______________________________________________________________________");
	Serial.printf("|*********************** Tic-Tac-Logic (game) ***********************|");
	Serial.printf("|** author:gofan-SiTu ***********************************************|");
	Serial.printf("|************************           请选择以下功能      *************|");
	Serial.printf("|************************            0：退出游戏          ***********|");
	Serial.printf("|************************     1：作为先手开始与电脑对弈   ***********|");
	Serial.printf("|************************     2：作为后手开始与电脑对弈   ***********|");
	Serial.printf("|********************************************************************|");
	Serial.printf("|——————————————————————————————————|");
	Serial.printf(">请输入对应序号：>>");
	cmd = scanf_int(1);
	switch (cmd)
	{
	case 0:
		exit(0);
	case 1:
		Serial.printf(">您选择与电脑对弈，落子时请输入行号和列号确定位置，中间用空格隔开\n");
		Serial.printf(">您的棋子是“o”,电脑的棋子是“X”\n");
		printQP(TicTacToe);
		Serial.printf(">您先走棋  ");
		while (1) {
			Serial.printf(">请输入您的下一步落子位置：>>");
			do {
				hang = scanf_int(1); 
        lie = scanf_int(1);
			} while (!inputQZ(TicTacToe, hang - 1, lie - 1));
			Serial.printf(">您走棋后，棋盘如下\n");
			printQP(TicTacToe);
			if (isPlayerWin(TicTacToe) == 1) {
				Serial.printf("\n>！恭喜玩家获胜 ！<\n >  您太强了  <\n");
				break;
			}
			else if (isPlayerWin(TicTacToe) == -1) {
				Serial.printf("\n >  电脑获胜  < \n >！你太菜拉！< \n");
				break;
			}
			else if (isQPFull(TicTacToe)) {
				Serial.printf(" >！平局 ！< \n");
				break;
			}
			position = computerPlay(TicTacToe);
			Serial.printf(" 电脑正在思考......\n");
			Serial.printf(">电脑的落子位置：>>%d %d\n>电脑落子后，棋盘如下\n", position / N + 1, position % N + 1);
			TicTacToe[position / N][position % N] = C_pawn;
			printQP(TicTacToe);
			if (isPlayerWin(TicTacToe) == 1) {
				Serial.printf("\n>！恭喜玩家获胜 ！<\n >  您太强了  <\n");
				break;
			}
			else if (isPlayerWin(TicTacToe) == -1) {
				Serial.printf("\n >  电脑获胜  < \n >！你太菜拉！< \n");
				break;
			}
			else if (isQPFull(TicTacToe)) {
				Serial.printf(" >！平局 ！< \n");
				break;
			}
		}
		break;
	case 2:
		Serial.printf(">您选择与电脑对弈，落子时请输入行号和列号确定位置，中间用空格隔开\n");
		Serial.printf(">您的棋子是“o”,电脑的棋子是“X”\n");
		Serial.printf(">电脑先走棋\n");
		while (1) {
			position = computerPlay(TicTacToe);
			Serial.printf(" 电脑正在思考......\n");
			Serial.printf(">电脑的落子位置：>>%d %d\n>电脑落子后，棋盘如下\n", position / N + 1, position % N + 1);
			TicTacToe[position / N][position % N] = C_pawn;
			printQP(TicTacToe);
			if (isPlayerWin(TicTacToe) == 1) {
				Serial.printf("\n>！恭喜玩家获胜 ！<\n >  您太强了  <\n");
				break;
			}
			else if (isPlayerWin(TicTacToe) == -1) {
				Serial.printf("\n >  电脑获胜  < \n >！你太菜拉！< \n");
				break;
			}
			else if (isQPFull(TicTacToe)) {
				Serial.printf(" >！平局 ！< \n");
				break;
			}
			Serial.printf(">请输入您的下一步落子位置：>>");
			do {
				hang = scanf_int(1);
        lie = scanf_int(1);
			} while (!inputQZ(TicTacToe, hang - 1, lie - 1));
			Serial.printf(">您走棋后，棋盘如下\n");
			printQP(TicTacToe);
			if (isPlayerWin(TicTacToe) == 1) {
				Serial.printf("\n>！恭喜玩家获胜 ！<\n >  您太强了  <\n");
				break;
			}
			else if (isPlayerWin(TicTacToe) == -1) {
				Serial.printf("\n >  电脑获胜  < \n >！你太菜拉！< \n");
				break;
			}
			else if (isQPFull(TicTacToe)) {
				Serial.printf(" >！平局 ！< \n");
				break;
			}

		}
		break;
	default:
		Serial.printf(">输入序号不准确，程序异常退出！\n 请重新启动！");
		exit(-1);
	}
	Serial.printf("\n  游戏结束！ \n");
	for (i = 0; i < N; i++)
		free(TicTacToe[i]);
	free(TicTacToe);
		Serial.printf("程序将关闭...\n", i);

}

void loop() {
  // put your main code here, to run repeatedly:

}
