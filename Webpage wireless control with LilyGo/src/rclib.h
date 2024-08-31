#ifndef __RCLIB_H__
#define __RCLIB_H__
#include <Arduino.h>
#include "driver/twai.h"

#include "config.h" // Pin configuration
#include <HardwareSerial.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <WiFi.h>

extern int num1;
extern int num2;
extern int Speed;
extern int Position;
extern int panduan;
extern int panduan1;
extern int yanshi;
extern int ii, j;
extern int c[99];
extern float a1, a2, a3, a4, a5, a6, a7, a8, p, q;
extern float b1[99], b2[99], b3[99], b4[99], b5[99], b6[99], b7[99], b8[99];
extern int txid;
#define LILYGO

#ifdef LILYGO
#define TX_PIN 27
#define RX_PIN 26
#else
#define TX_PIN 17
#define RX_PIN 18
#endif

bool rc_init();
void rc_estop(int);                     // Emergency stop
void rc_set_status(int, uint8_t);       // Set motor status
int rc_read_status(int);                // Read motor status
void rc_set_mode(int, uint8_t);         // Set motor mode
int rc_read_mode(int);                  // Read motor mode
void rc_set_zp(int, uint8_t);           // Set current position as zero point
void rc_set_PID(int, uint8_t, float);   // Set PID parameters
float rc_read_PID(int, uint8_t);        // Read PID parameters
void rc_set_lim(int, uint8_t, float);   // Set limit parameters
float rc_read_lim(int, uint8_t);        // Read limit parameters
void rc_spr(int, float);                // Single point run
void rc_spt(int, float, float);         // Single point trajectory
void rc_set_ctp(int, uint16_t, float);  // Set continuous trajectory position data
void rc_set_ctv(int, uint16_t, float);  // Set continuous trajectory speed data
void rc_set_ctmf(int, uint16_t, float); // Set continuous trajectory torque data
void rc_tdr(int, uint16_t);             // Run specified trajectory data
void rc_record(int, uint16_t);          // Record data to a specified index position
float rc_read_rd(int, uint8_t);         // Read running data
void rc_set_CAN_ID(int, uint8_t);       // Set CAN ID
void rc_reset(int);                     // Restore settings

#endif
