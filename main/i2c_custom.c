/*
 * i2c_custom.c
 *
 *  Created on: Apr 22, 2021
 *      Author: scott
 */
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "i2c_custom.h"

void i2c_custom_write(uint8_t w_r_reg, uint8_t cntrl_reg, uint8_t data){

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, w_r_reg, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, cntrl_reg, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, data, ACK_CHECK_EN);
	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

}

void i2c_custom_read(uint8_t *data_rd,uint8_t reg, uint8_t write_addr, uint8_t read_addr){

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, write_addr, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

	vTaskDelay(30 / portTICK_RATE_MS);

	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, read_addr, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, data_rd, NACK_VAL);
	i2c_master_stop(cmd);
	i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
}

void i2c_master_init(void)
{
	int i2c_master_port = I2C_MASTER_NUM;

	i2c_config_t conf = {
	    .mode = I2C_MODE_MASTER,
	    .sda_io_num = I2C_MASTER_SDA_IO,         // select GPIO specific to your project
	    .sda_pullup_en = GPIO_PULLUP_ENABLE,
	    .scl_io_num = I2C_MASTER_SCL_IO,         // select GPIO specific to your project
	    .scl_pullup_en = GPIO_PULLUP_ENABLE,
	    .master.clk_speed = I2C_MASTER_FREQ_HZ,  // select frequency specific to your project
	    // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
	};

    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
