#include "SZQ_engine.h"
int scoretable[6][2] = { {C_pawn + C_pawn,50},
						 {P_pawn + P_pawn,30},
						 {C_pawn + ' ',6},
						 {P_pawn + ' ',4},
						 {' ' +' ',2},
						 {P_pawn + C_pawn,1},
};

int row_score(char** QP,int row){
	int score=0;
	int type = 0;
	for (int i = 0; i < N; i++)
	{
		type = QP[row][i] + type;
	}
    //将落点对应那一行三个位置的字符相加，减去自身的空字符，得到类型type
	type = type - ' ';
    //查询打分表，type类型的对应得分score
	for (int k = 0; k < 6; k++)
	{
		if (scoretable[k][0] == type)
		{
			score = scoretable[k][1]; 
			break;
		}
	}
	return score;
}

int column_score(char** QP, int column) {
	int score = 0;
	int type = 0;
    //将落点对应那一列三个位置的字符相加，减去自身的空字符，得到类型type
	for (int i = 0; i < N; i++)
	{
		type = QP[i][column] + type;
	}
	type = type - ' ';
    //查询打分表，type类型的对应得分score
	for (int k = 0; k < 6; k++)
	{
		if (scoretable[k][0] == type)
		{
			score = scoretable[k][1];
			break;
		}
	}
	return score;
}


int Pdiag_score(char** QP, int postion) {
	int score = 0;
	int type ;
    //判断该位置是否存在正对角情况
	if (postion/N==postion%N)
	{
        //若存在，同样的将落点对应那一正对角三个位置的字符相加，减去自身的空字符，得到类型type
		type = QP[0][0] + QP[1][1] + QP[2][2];
		type = type - ' ';
        //查询打分表，type类型的对应得分score
		for (int k = 0; k < 6; k++)
		{
			if (scoretable[k][0] == type)
			{
				score = scoretable[k][1];
				break;
			}
		}
	}
	return score;
}

int Ndiag_score(char** QP, int postion) {
	int score = 0;
	int type;
    //判断该位置是否存在反对角情况，自行证明反对角满足(postion / N+postion % N)==2
	if ((postion / N+postion % N)==2)
	{
		type = QP[0][2] + QP[1][1] + QP[2][0];
		type = type - ' ';
		for (int k = 0; k < 6; k++)
		{
			if (scoretable[k][0] == type)
			{
				score = scoretable[k][1];
				break;
			}
		}
	}
	return score;
}

int computerPlay(char** QP) {
	int index=0;
	int score = 0;

	for (int i = 0; i < N*N; i++)
	{
		int temp_score = 0;
        //遍历棋盘，并且找出空格符，即可落子的位置，计算分数
		if (QP[i / N][i % N] == ' ')
		{
            //把4种情况的分数相加得到总分数
			temp_score = row_score(QP, i/N) + column_score(QP, i%N) + Pdiag_score(QP, i) + Ndiag_score(QP, i);
			if (temp_score > score)   //取分数最大值
			{
				score = temp_score;
				index = i;
			}
			else if (temp_score == score)  //若分数相同，在两个随机选择一个位置作为落点
			{
				srand((unsigned)millis());
				index=(rand() % 2)? i:index;
			}	
		}
	}
	return index;
}

