//game.c
#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
extern int WinNum;

//初始化棋盘
void init_board(char board[board_size][board_size])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < board_size; i++)
	{
		for (j = 0; j < board_size; j++)
		{
			board[i][j] = EMPTY;
		}
	}
}

//打印棋盘
void display_board(char board[board_size][board_size])
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	Serial.printf(" ");
	for (i = 1; i <= board_size; i++)
	{
		if (10 == i)
		{
			Serial.printf(" ");
		}
		Serial.printf("  %2d", i);
	}
	Serial.printf("\n");
	for (i = 0; i <= 2 * board_size; i++)
	{
		if (i % 2 == 0)
		{
			for (j = 0; j <= board_size; j++)
			{
				if (j != 0)
				{
					Serial.printf("---|");
				}
				else
				{
					Serial.printf("  |");
				}
			}
		}
		else
		{
			for (j = 0; j <= board_size; j++)
			{
				if (j == 0)
				{
					Serial.printf("%2d|", i / 2 + 1);
				}
				else
				{
					tmp = i / 2;
					Serial.printf(" %c |", board[tmp][j - 1]);
				}
			}
		}

		Serial.printf("\n");
	}
}

// 判断位置是否为空
int isPositionEmpty(char board[board_size][board_size], int x, int y) 
{
	return board[x][y] == EMPTY;
}

//玩家下棋
void player_move(char board[board_size][board_size])
{
	int x = 0;
	int y = 0;
	while (1)
	{
		x = scanf_int(1);
    y = scanf_int(1);
		//判断输入是否合法
		if ((x >= 1 && x <= board_size) && (y >= 1 && y <= board_size))
		{
			if (isPositionEmpty(board, x - 1, y - 1))
			{
				board[x - 1][y - 1] = PLAYER;
				break;
			}
			else
			{
				Serial.printf("该位置已有棋子, 请重新输入！\n");
			}
		}
		else
		{
			Serial.printf("输入非法，请重新输入！\n");
		}
	}
}

// 判断当前位置是否为有效的落子点
bool isValidMove(int x, int y) 
{
	// 判断 (x, y) 是否在棋盘范围内，这里假设棋盘大小为board_size
	if (x < 0 || x >= board_size || y < 0 || y >= board_size) 
	{
		return false;
	}
	return true;
}

// 判断五N子棋游戏是否结束并返回胜利方
char check_win(char board[board_size][board_size])
{
	// 定义四个方向：水平、垂直、左上到右下、右上到左下
	int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	int n = board_size;// 棋盘大小

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == EMPTY) {
				continue;  // 当前位置没有棋子，跳过
			}
			char player = board[i][j];
			for (int k = 0; k < 4; k++) { // 遍历四个方向
				int dx = directions[k][0]; // 方向的 x 坐标增量
				int dy = directions[k][1]; // 方向的 y 坐标增量
				int count = 1;  // 当前位置已有棋子，计数从1开始
				int x = i + dx;
				int y = j + dy;

				while (isValidMove(x, y) && board[x][y] == player) { // 沿当前方向连续相同颜色的棋子数
					count++;
					x += dx;
					y += dy;
				}

				if (count >= WinNum) {
					return player;  // 有一方获胜，返回胜利方
				}
			}
		}
	}

	// 判断棋盘是否已满，即平局
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == EMPTY) {
				return NOFULL;  // 棋盘还未满
			}
		}
	}
	return FULL;  // 棋盘已满平局
}

// 判断五N子棋游戏加权连子数，以及棋型并给予相应的得分
int evaluate_count(char board[board_size][board_size])
{
	int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	// 定义四个方向的增量数组，分别表示横向、纵向、左上到右下斜向、右上到左下斜向
	int n = board_size;
	int count;
	int sorce = 0; // 初始化计数器和得分
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j] == EMPTY) 
			{
				continue;  // 当前位置没有棋子，跳过
			}
			char player = board[i][j];
			for (int k = 0; k < 4; k++) 
			{
				int dx = directions[k][0];
				int dy = directions[k][1];
				count = 1;  // 当前位置已有棋子，计数从1开始
				int x = i + dx;
				int y = j + dy;

				while (isValidMove(x, y) && board[x][y] == player) 
				{
					count++;
					x += dx;
					y += dy;
				} // 在当前方向上统计连续的棋子个数，直到边界或者不是同一种棋子

				if (player == AI)
				{
					sorce += 20 * (int)pow(count, 2);// AI连成其他长度的连子，基于平方的得分增加
				}
				if (player == PLAYER)
				{
					sorce -= 30 * (int)pow(count, 2); // 玩家连成其他长度的连子，基于平方的得分减少
				}

				// 判断棋型并给予相应的得分
				if (count == WinNum)
				{
					if (player == AI)
						sorce += 1000;  // “活五”，AI得分加1000
					else if (player == PLAYER)
						sorce -= 1500;  // “活五”，玩家得分减1500
				}
				else if (count == WinNum - 1)
				{
					if ((player == AI && isPositionEmpty(board, x + dx, y + dy) && isPositionEmpty(board, i - dx, j - dy)) ||
						(player == PLAYER && isPositionEmpty(board, x + dx, y + dy) && isPositionEmpty(board, i - dx, j - dy)))
					{
						if (player == AI)
							sorce += 800;  // “活四”，AI得分加800
						else if (player == PLAYER)
							sorce -= 1200;  // “活四”，玩家得分减1200
					}
				}
				else if (count == WinNum - 2)
				{
					if ((player == AI && isPositionEmpty(board, x + dx, y + dy) && isPositionEmpty(board, x - 2 * dx, y - 2 * dy) &&
						isPositionEmpty(board, i - dx, j - dy) && isPositionEmpty(board, i + 2 * dx, j + 2 * dy)) ||
						(player == PLAYER && isPositionEmpty(board, x + dx, y + dy) && isPositionEmpty(board, x - 2 * dx, y - 2 * dy) &&
							isPositionEmpty(board, i - dx, j - dy) && isPositionEmpty(board, i + 2 * dx, j + 2 * dy)))
					{
						if (player == AI)
							sorce += 300;  // “活三”，AI得分加300
						else if (player == PLAYER)
							sorce -= 400;  // “活三”，玩家得分减400
					}
				}


			}
		}
	}
	return sorce;
}

//评估当前局面的得分
int evaluate(char board[board_size][board_size], int i, int j)
{
	int sorce = evaluate_count(board);// 先调用evaluate_count函数计算基本得分
	sorce += (1000/sqrt((i + 1 - board_size/2) * (i + 1 - board_size/2) + (j + 1 - board_size/2) * (j + 1 - board_size/2))/ board_size);
	// 根据棋盘中心的距离对基本得分进行调整，离中心越远，得分越低
	return sorce;
}

// 极小化极大算法
int minimax(char board[board_size][board_size], int depth, int isMaximizingPlayer, int i, int j)
{
	// 如果达到指定深度或游戏结束，则返回当前局面的得分
	if (depth == 0 || check_win(board) != NOFULL) 
	{
		return evaluate(board, i, j); // 如果游戏结束，则返回当前局面的得分
	}

	if (isMaximizingPlayer) // 最大化玩家（AI）
	{
		int maxEval = -1000000;// 初始化最大得分为负无穷大
		int i, j;
		for (i = 0; i < board_size; i++) {
			for (j = 0; j < board_size; j++) {
				if (board[i][j] == EMPTY) { // 检查该位置是否为空格
					board[i][j] = AI; // 假设AI在该位置下棋
					int eval = minimax(board, depth - 1, 0, i, j); // 递归搜索子节点，切换到最小化玩家
					board[i][j] = EMPTY; // 恢复该位置为空格
					if (eval > maxEval) {
						maxEval = eval; // 更新最大得分
					}
				}
			}
		}
		return maxEval;
	}
	else {  // 最小化玩家（玩家）
		int minEval = 1000000; // 初始化最小得分为正无穷大
		int i, j;
		for (i = 0; i < board_size; i++) {
			for (j = 0; j < board_size; j++) {
				if (board[i][j] == EMPTY) { // 检查该位置是否为空格
					board[i][j] = PLAYER; // 假设玩家在该位置下棋
					int eval = minimax(board, depth - 1, 1, i, j); // 递归搜索子节点，切换到最小化玩家
					board[i][j] = EMPTY; // 恢复该位置为空格
					if (eval < minEval) {
						minEval = eval; // 更新最小得分
					}
				}
			}
		}
		return minEval;
	}
}

// AI 下棋
void ai_move(char board[board_size][board_size])
{
	int bestEval = -1000000;// 初始化最优得分为负无穷大
	int bestRow = -1;// 初始化最优位置的行号
	int bestCol = -1;// 初始化最优位置的列号
	int depth = 0;//递归深度，深度越高耗时越长
	// 根据棋盘大小确定递归深度
	if (board_size < 4){
		depth = 6;
	}
	else if (board_size < 5){
		depth = 5;
	}
	else if (board_size < 7){
		depth = 4;
	}
	else if (board_size < 9){
		depth = 3;
	}
	else{
		depth = 2;
	}

	int i, j;
	for (i = 0; i < board_size; i++) {
		for (j = 0; j < board_size; j++) {
			if (board[i][j] == EMPTY) {
				board[i][j] = AI; // 假设AI在该位置下棋
				int eval = minimax(board, depth, 0, i, j); // 调用极小化极大算法计算得分
				board[i][j] = EMPTY; // 恢复该位置为空格
				if (eval > bestEval) {
					bestEval = eval; // 更新最优得分
					bestRow = i;// 更新最优位置的行号
					bestCol = j;// 更新最优位置的列号
				}
			}
		}
	}
  Serial.printf("\n[DEBUG]bestEval= %d  bestRow= %d  bestCol= %d\n",bestEval,bestRow+1,bestCol+1);
	// 在最优位置下棋
	board[bestRow][bestCol] = AI;
}
