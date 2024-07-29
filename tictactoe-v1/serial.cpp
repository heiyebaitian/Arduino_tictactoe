//serial.cpp
#include "serial.h"

int scanf_int(int length){
  int i = 0;
  String inString = "" ; //串口接收命令存放区
  while(i<length){
    while(Serial.available()>0){ //检查缓冲区是否存在数据
      inString += char(Serial.read()); //读取缓冲区
      i++;
    }
  }
  return inString.toInt();
}