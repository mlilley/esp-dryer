#ifndef __MENU_HANDLER_H__
#define __MENU_HANDLER_H__

#include "common.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void setupMenuHandler(Adafruit_SSD1306* display, profile_t profiles[], int nProfiles, xQueueHandle queueInput);
void taskMenuHandler(void* params);

#endif