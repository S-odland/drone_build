/*
 * i2c_custom.h
 *
 *  Created on: Apr 22, 2021
 *      Author: scott
 */

#ifndef MAIN_I2C_CUSTOM_H_
#define MAIN_I2C_CUSTOM_H_

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#define CONFIG_I2C_SLAVE_SCL 5
#define CONFIG_I2C_SLAVE_SDA 4

#define CONFIG_I2C_MASTER_SCL 19
#define CONFIG_I2C_MASTER_SDA 18
#define CONFIG_I2C_MASTER_PORT_NUM 1
#define CONFIG_I2C_MASTER_FREQUENCY 100000

#define CONFIG_I2C_MASTER_PORT_NUM 1

#define _I2C_NUMBER(num) I2C_NUM_##num
#define I2C_NUMBER(num) _I2C_NUMBER(num)

#define DATA_LENGTH 512                  /*!< Data buffer length of test buffer */
#define RW_TEST_LENGTH 128               /*!< Data length for r/w test, [0,DATA_LENGTH] */
#define DELAY_TIME_BETWEEN_ITEMS_MS 1000 /*!< delay time between different test items */

#define I2C_MASTER_SCL_IO CONFIG_I2C_MASTER_SCL               /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO CONFIG_I2C_MASTER_SDA               /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUMBER(CONFIG_I2C_MASTER_PORT_NUM) /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ CONFIG_I2C_MASTER_FREQUENCY        /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

void i2c_custom_write(uint8_t w_r_reg, uint8_t cntrl_reg, uint8_t data);
void i2c_custom_read(uint8_t *data_rd,uint8_t reg, uint8_t write_addr, uint8_t read_addr);
void i2c_master_init();

#endif /* MAIN_I2C_CUSTOM_H_ */
