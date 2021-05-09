

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
#include "custom_wifi.h"
#include "websocket.h"

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

		//printf("GYRO [X, Y, Z]: %d %d %d\n",*(gyro),*(gyro+1),*(gyro+2));
		//printf("ACCEL [X, Y, Z]: %d %d %d\n",*(accel),*(accel+1),*(accel+2));

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

    // wifi

	ESP_LOGI("WEBSOCKET", "[APP] Startup..");
	ESP_LOGI("WEBSOCKET", "[APP] Free memory: %d bytes", esp_get_free_heap_size());
	ESP_LOGI("WEBSOCKET", "[APP] IDF version: %s", esp_get_idf_version());
	esp_log_level_set("*", ESP_LOG_INFO);
	esp_log_level_set("WEBSOCKET_CLIENT", ESP_LOG_DEBUG);
	esp_log_level_set("TRANS_TCP", ESP_LOG_DEBUG);

	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	ESP_LOGI("wifi softAP", "ESP_WIFI_MODE_AP");
	wifi_init_softap();


//
//	/* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
//	 * Read "Establishing Wi-Fi or Ethernet Connection" section in
//	 * examples/protocols/README.md for more information about this function.
//	 */
//	ESP_ERROR_CHECK(example_connect());
//
//	websocket_app_start();

    xTaskCreate(imu_data_task, "imu_data_task", 1024 * 2, NULL, 1, NULL);

}
