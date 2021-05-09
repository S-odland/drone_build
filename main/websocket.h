/*
 * websocket.h
 *
 *  Created on: Apr 29, 2021
 *      Author: scott
 */

#ifndef MAIN_WEBSOCKET_H_
#define MAIN_WEBSOCKET_H_


#include <stdio.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_websocket_client.h"
#include "esp_event.h"

#define WEBSOCKET_URI "ws://echo.websocket.org/"
#define WEBSOCKET_URI_FROM_STRING 1

void shutdown_signaler(TimerHandle_t xTimer);
void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
void websocket_app_start(void);

#endif /* MAIN_WEBSOCKET_H_ */
