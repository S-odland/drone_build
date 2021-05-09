/*
 * custom_wifi.h
 *
 *  Created on: Apr 28, 2021
 *      Author: scott
 */

#ifndef MAIN_CUSTOM_WIFI_H_
#define MAIN_CUSTOM_WIFI_H_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_https_server.h"

#include "lwip/err.h"
#include "lwip/sys.h"


#define ESP_WIFI_SSID      "drone_wifi"
#define ESP_WIFI_PASS      "ee327_scott"
#define ESP_WIFI_CHANNEL   1
#define MAX_STA_CONN       4

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void wifi_init_softap(void);

#endif /* MAIN_CUSTOM_WIFI_H_ */
