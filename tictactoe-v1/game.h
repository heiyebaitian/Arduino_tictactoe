//game.h
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include "serial.h"

//定义棋盘大小(可更改)
#define board_size 3

// 定义玩家和AI的棋子类型
#define PLAYER 'X'
#define AI 'O'
// 定义符号
#define EMPTY ' '
#define NOFULL '-'
#define FULL '*'

//初始化棋盘
void init_board(char board[board_size][board_size]);
//打印棋盘
void display_board(char board[board_size][board_size]);
//判断位置是否为空
int isPositionEmpty(char board[board_size][board_size], int x, int y);
//玩家下棋
void player_move(char board[board_size][board_size]);
// 判断当前位置是否为有效的落子点
bool isValidMove(int x, int y);
// 判断N子棋游戏加权连子数，以及棋型并给予相应的得分
char check_win(char board[board_size][board_size]);
// 判断N子棋游戏连子数
int evaluate_count(char board[board_size][board_size]);
//评估当前局面的得分
int evaluate(char board[board_size][board_size], int i, int j);
// 极小化极大算法
int minimax(char board[board_size][board_size], int depth, int isMaximizingPlayer, int i, int j);
// AI 下棋
void ai_move(char board[board_size][board_size]);
