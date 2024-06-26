#ifndef __TEST_H__
#define __TEST_H__
#include <Arduino.h>
#include "config.h"
#include <HardwareSerial.h>
#include <ESP32CAN.h>
#include <CAN_config.h>
#include <SPI.h>



void Motor1_p1();
void Motor2_p1();
void Motor3_p1();
void Motor4_p1();
void Motor5_p1();

void Motor1_p2();
void Motor2_p2();
void Motor3_p2();
void Motor4_p2();
void Motor5_p2();

void Motor1_zero();
void Motor2_zero();
void Motor3_zero();
void Motor4_zero();
void Motor5_zero();

void Motor6_p90();
void Motor6_zero();

void Motor7_open();
void Motor7_close();

void Motor1_enable();
void Motor2_enable();
void Motor3_enable();
void Motor4_enable();
void Motor5_enable();
void Motor6_enable();
void Motor7_enable();

#endif