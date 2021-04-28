

/* i2c - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "imu.h"
#include "i2c_custom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//static const char *TAG = "main";
void imu_data_task(void *pvParameters);

SemaphoreHandle_t print_mux = NULL;

void imu_data_task(void *pvParameters){

	signed short gyro[3] = {0,0,0};
	signed short accel[3] = {0,0,0};

	while(1) {

		read_imu_data((gyro),IMU_OUTX_L_G);
		read_imu_data((gyro+1),IMU_OUTY_L_G);
		read_imu_data((gyro+2),IMU_OUTZ_L_G);
		read_imu_data((accel),IMU_OUTX_L_XL);
		read_imu_data((accel+1),IMU_OUTY_L_XL);
		read_imu_data((accel+2),IMU_OUTZ_L_XL);

		printf("GYRO [X, Y, Z]: %d %d %d\n",*(gyro),*(gyro+1),*(gyro+2));
		printf("ACCEL [X, Y, Z]: %d %d %d\n",*(accel),*(accel+1),*(accel+2));

		detect_tilt_loc(accel);

		//vTaskDelay(100 / portTICK_PERIOD_MS);
	}

}

void app_main(void)
{
	// setup
    //print_mux = xSemaphoreCreateMutex();
    i2c_master_init();
    imu_setup();
    led_setup();

    xTaskCreate(imu_data_task, "imu_data_task", 1024 * 2, NULL, 1, NULL);

}
