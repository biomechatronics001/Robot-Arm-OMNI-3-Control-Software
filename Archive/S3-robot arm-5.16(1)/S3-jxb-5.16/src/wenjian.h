#ifndef __WENJIAN_H__
#define __WENJIAN_H__
#include <string.h>
#include <stdio.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "spiffs.h"
void init_spiffs(void);//初始化
void ds_spiffs_test(void);//测试
void ds_spiffs_deinit(void);//卸载

#endif