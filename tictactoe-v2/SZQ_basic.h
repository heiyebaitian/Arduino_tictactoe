//`SZQ_basic.h`
#ifndef SZQ_BASIC_H  
#define SZQ_BASIC_H

#include<Arduino.h>
#include "serial.h"
#include<stdio.h>
#include <string.h>
#include<stdlib.h>


#define N 3
#define P_pawn 'o' //玩家棋子 o
#define C_pawn 'X' //电脑棋子 X

char** creatQP(); //创建棋盘
void printQP(char** QP); //打印棋盘
int inputQZ(char** QP, int row, int column); //输入棋子
int isPlayerWin(char** QP); //判断胜负
int isQPFull(char** QP); //判断平局


#endif