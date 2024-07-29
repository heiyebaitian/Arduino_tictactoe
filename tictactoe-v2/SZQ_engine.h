#ifndef SZQ_ENGINE_H  
#define SZQ_ENGINE_H


#include "SZQ_basic.h"
#include "serial.h"
#include<Arduino.h>


int computerPlay(char** QP);

int row_score(char** QP, int row);
int column_score(char** QP, int column);
int Pdiag_score(char** QP, int postion);
int Ndiag_score(char** QP, int postion);

#endif