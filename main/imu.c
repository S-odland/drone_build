/*
 * imu.c
 *
 *  Created on: Apr 22, 2021
 *      Author: scott
 */

#include "imu.h"
#include "i2c_custom.h"


void imu_setup() {

	uint8_t who;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, IMU_ADDR_WRITE, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, IMU_WHOAMI, ACK_CHECK_EN);
	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

	vTaskDelay(30 / portTICK_RATE_MS);

	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, IMU_ADDR_READ, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, &who, NACK_VAL);
	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

	if (who != 0b01101001){
		while(1)
		{
			printf("who: %d\n",who);
		}
	}

	// init IMU_CTRL1_XL
	i2c_custom_write(IMU_ADDR_WRITE,IMU_CTRL1_XL,0b10000010);

	// init IMU_CTRL2_G
	i2c_custom_write(IMU_ADDR_WRITE,IMU_CTRL2_G,0b10001000);

	// init IMU_CTRL3_C
	i2c_custom_write(IMU_ADDR_WRITE,IMU_CTRL3_C,0b00000100);

}

void led_setup(){
	// identify pins as GPIOs
    gpio_pad_select_gpio(LED_1);
    gpio_pad_select_gpio(LED_2);
    gpio_pad_select_gpio(LED_3);
    gpio_pad_select_gpio(LED_4);
    gpio_pad_select_gpio(LED_5);
    gpio_pad_select_gpio(LED_6);
    gpio_pad_select_gpio(LED_7);
    gpio_pad_select_gpio(LED_8);
    gpio_pad_select_gpio(LED_9);
    gpio_pad_select_gpio(LED_10);

    // setting pins as outputs
    gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_5, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_6, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_7, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_8, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_9, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_10, GPIO_MODE_OUTPUT);

	reset_leds();

}

void reset_leds() {
	gpio_set_level(LED_1, 0);
	gpio_set_level(LED_2, 0);
	gpio_set_level(LED_3, 0);
	gpio_set_level(LED_4, 0);
	gpio_set_level(LED_5, 0);
	gpio_set_level(LED_6, 0);
	gpio_set_level(LED_7, 0);
	gpio_set_level(LED_8, 0);
	gpio_set_level(LED_9, 0);
	gpio_set_level(LED_10,0);
}

void read_imu_data(signed short *data_rd,uint8_t reg) {

	unsigned char data1;
	unsigned char data2;

	i2c_custom_read(&data1,reg,IMU_ADDR_WRITE,IMU_ADDR_READ);
	i2c_custom_read(&data2,reg + 0x01,IMU_ADDR_WRITE,IMU_ADDR_READ);

	*data_rd = (data2 << 8) | data1;

	scale_data(data_rd);

}

void scale_data(signed short *data) {
	*data = 16 * (*data) / 16383;
}

/*          LED LOCATIONS
 *
 *   (led_1) 	 O O    (led_10)
 *   (led_2)   O     O  (led_9)
 *   (led_3)  O       O (led_8)
 *   (led_4)   O     O  (led_7)
 *   (led_5)     O O    (led_6)
 *
 */

void detect_tilt_loc(signed short gyro_data[3]){

	signed short x = *(gyro_data);
	signed short y = *(gyro_data+1);
	//signed short z = *(gyro_data+2);

	float mag = abs(x) + abs(y);
	float mag_x = abs(x)/mag;
	float mag_y = abs(y)/mag;

	if (x > 0 && y > 0) {

		if (mag_y > mag_x) {
			reset_leds();
			gpio_set_level(LED_4,1);
		} else {
			reset_leds();
			gpio_set_level(LED_5,1);
		}

	} else if (x < 0 && y > 0) {

		if (mag_y > mag_x) {
			reset_leds();
			gpio_set_level(LED_2,1);
		} else {
			reset_leds();
			gpio_set_level(LED_1,1);
		}

	} else if (x < 0 && y < 0) {

		if (mag_y > mag_x) {
			reset_leds();
			gpio_set_level(LED_9,1);
		} else {
			reset_leds();
			gpio_set_level(LED_10,1);
		}

	} else if (x > 0 && y < 0) {

		if (mag_y > mag_x) {
			reset_leds();
			gpio_set_level(LED_7,1);
		} else {
			reset_leds();
			gpio_set_level(LED_6,1);
		}

	} else if (x == 0 && y > 0) {

		reset_leds();
		gpio_set_level(LED_3,1);

	} else if ( x == 0 && y < 0) {

		reset_leds();
		gpio_set_level(LED_8,1);

	} else {

		reset_leds();

	}

}

