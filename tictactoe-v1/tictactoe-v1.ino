#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"
#include "serial.h"

// 定义胜利条件
int WinNum = 0;
// 系统运行时间记录
uint32_t timecnt = 0;


bool display_win(char board[board_size][board_size])
{
	if (check_win(board) == PLAYER)
	{
		display_board(board); // 最终显示棋盘
		Serial.printf("玩家胜利！\n");
		return true;
	}
	else if (check_win(board) == AI)
	{
		display_board(board); // 最终显示棋盘
		Serial.printf("AI 胜利！\n");
		return true;
	}
	else if (check_win(board) == FULL)
	{
		display_board(board); // 最终显示棋盘
		Serial.printf("平局！\n");
		return true;
	}
	return false;
}

void game(char board[board_size][board_size])
{
	int is_player_turn = 0; // 玩家先手
	Serial.printf("************************\n");
	Serial.printf("****** 1.玩家先手 ******\n");
	Serial.printf("****** 0.AI先手  *******\n");
	Serial.printf("************************\n");
	Serial.printf("请输入:>");
	is_player_turn =  scanf_int(1);
	int turn = 0; // 回合数
	init_board(board);

	// 游戏循环
	while (1) 
	{
		turn++;
		if (is_player_turn)
		{
			Serial.printf("***** %d子棋游戏！*****\n", WinNum);
			display_board(board); // 显示棋盘
			Serial.printf("请玩家输入坐标下棋：>\n");
			player_move(board); // 玩家下棋
			if (display_win(board))
				break;
			display_board(board); // 显示棋盘
      timecnt = millis();
			Serial.printf("AI正在下棋！\n");
			ai_move(board); // AI 下棋
      Serial.printf("AI计算耗时：%dms\n",millis()-timecnt);
			if (display_win(board))
				break;
		}
		else
		{
			Serial.printf("***** %d子棋游戏！*****\n", WinNum);
			display_board(board); // 显示棋盘
      timecnt = millis();
			Serial.printf("AI正在下棋！\n");
			if (turn == 1)
			{
				board[board_size/2][board_size / 2] = AI;
			}
			else
			{
				ai_move(board); // AI 下棋
        Serial.printf("AI计算耗时：%dms\n",millis()-timecnt);
				if (display_win(board))
					break;
			}
			Serial.printf("***** %d子棋游戏！*****\n", WinNum);
			display_board(board); // 显示棋盘
			Serial.printf("请玩家输入坐标下棋：>\n");
			player_move(board); // 玩家下棋
			if (display_win(board))
				break;
		}
	}
	Serial.printf("总共进行了 %d 回合。\n", turn);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
		while (1)
		{
			Serial.printf("请输入连胜棋子个数：>");
			WinNum =  scanf_int(1);
			if (WinNum > board_size)
			{
				Serial.printf("输入的连胜棋子个数已超过棋盘大小，请重新输入，或者调整棋盘大小\n");
			}
			else
			{
				Serial.printf("**** %d子棋游戏开始 ****\n", WinNum);
				break;
			}
		}
	char board[board_size][board_size] = { 0 }; //创建棋盘
	game(board);
}
