#ifndef __RCLIB_H__
#define __RCLIB_H__
#include <Arduino.h>
#include "driver/twai.h"
#include "config.h" //引脚配置
#include <HardwareSerial.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <WiFi.h>


extern int Speed;
extern int Position;
extern int panduan;
extern int panduan1;
extern int yanshi;
extern int ID;
extern int ii, j;
extern int c[99];
extern float a1, a2, a3, a4, a5, a6, a7, a8;
extern float b1[99], b2[99], b3[99], b4[99], b5[99], b6[99], b7[99], b8[99];
#define LILYGO

#ifdef LILYGO
#define TX_PIN 27
#define RX_PIN 26
#else
#define TX_PIN 17
#define RX_PIN 18
#endif

bool rc_init();
void rc_estop(int);                     // 急停 emergency stop
void rc_set_status(int, uint8_t);       // 设置电机状态 set motor status
int rc_read_status(int);                // 读取电机状态 read motor status
void rc_set_mode(int, uint8_t);         // 设置电机模式 set motor mode
int rc_read_mode(int);                  // 读取电机模式 read motor mode
void rc_set_zp(int, uint8_t);           // 设置当前位置为零点 set current position to zero
void rc_set_PID(int, uint8_t, float);   // 设置PID参数 set PID parameters
float rc_read_PID(int, uint8_t);        // 读取PID参数 read PID parameters
void rc_set_lim(int, uint8_t, float);   // 设置限制参数 set limit parameters
float rc_read_lim(int, uint8_t);        // 读取限制参数 read limit parameters
void rc_spr(int, float);                // 单点运行 single-point operation
void rc_spt(int, float, float);         // 单点轨迹 single-point trajectory
void rc_set_ctp(int, uint16_t, float);  // 设置连续轨迹位置数据 set continuous trajectory position data
void rc_set_ctv(int, uint16_t, float);  // 设置连续轨迹速度数据 set continuous trajectory velocity data
void rc_set_ctmf(int, uint16_t, float); // 设置连续轨迹矩流数据 set continuous trajectory torque data
void rc_tdr(int, uint16_t);             // 指定轨迹数据运行 set trajectory data running
void rc_record(int, uint16_t);          // 记录数据到指定索引位置 record data to the specified index position
float rc_read_rd(int, uint8_t);         // 读取运行数据 read run data
void rc_set_CAN_ID(int, uint8_t);       // 设置CAN ID set CAN ID
void rc_reset(int);                     // 还原设置 restore settings


#endif