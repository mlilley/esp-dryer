#ifndef __MENU_HANDLER_H__
#define __MENU_HANDLER_H__

#include "common.h"
#include "ConfigStore.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void setupMenuHandler(ConfigStore* config, xQueueHandle queueInput, Adafruit_SSD1306* display);
void taskMenuHandler(void* params);

#endif