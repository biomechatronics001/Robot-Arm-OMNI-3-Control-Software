#ifndef __TEST_H__
#define __TEST_H__
#include <Arduino.h>
#include "config.h" //引脚配置
#include <HardwareSerial.h>
#include <ESP32CAN.h>
#include <CAN_config.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//extern int rxmotortemp[4];
//extern int rxmotortur[4];
//extern int rxmotorspeed[4];
//extern int rxmotorposition[4];

//void positionrun(int, int32_t); // 位置运行
void speedrun(int32_t speed); // 速度运行
void rotaterun(int32_t speed);//原地旋转运行
//int read_rd(int, int);   // 读取位置
void STOP();

#endif