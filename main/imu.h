/*
 * imu.h
 *
 *  Created on: Apr 22, 2021
 *      Author: scott
 */

#ifndef MAIN_IMU_H_
#define MAIN_IMU_H_

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define IMU_WHOAMI 0x0F
#define IMU_ADDR_READ 0b11010111
#define IMU_ADDR_WRITE 0b11010110
#define IMU_CTRL1_XL 0x10
#define IMU_CTRL2_G 0x11
#define IMU_CTRL3_C 0x12
#define IMU_OUT_TEMP_L 0x20
#define IMU_OUTX_L_G 0x22
#define IMU_OUTY_L_G 0x24
#define IMU_OUTZ_L_G 0x26
#define IMU_OUTX_L_XL 0x28
#define IMU_OUTY_L_XL 0x2A
#define IMU_OUTZ_L_XL 0x2C

#define LED_1  12
#define LED_2  13
#define LED_3  14
#define LED_4  25
#define LED_5  26
#define LED_6  27
#define LED_7  32
#define LED_8  33
#define LED_9  22
#define LED_10 23

#define TOP_TILT          {-16,0,0}
#define TOP_RIGHT_TILT    {-11,-11,0}
#define RIGHT_TILT        {0,-16,0}
#define BOTTOM_RIGHT_TILT {11,-11,0}
#define BOTTOM_TILT       {16,0,0}
#define BOTTOM_LEFT_TILT  {11,11,0}
#define LEFT_TILT         {0,16,0}
#define TOP_LEFT_TILT     {-11,11,0}
#define FLAT              {0,0,-15}

void imu_setup();
void led_setup();
void reset_leds();
void read_imu_data(signed short *data_rd,uint8_t reg);
void scale_data(signed short *data);
void detect_tilt_loc(signed short gyro_data[3]);

#endif /* MAIN_IMU_H_ */
