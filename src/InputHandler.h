#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include "common.h"
#include <Arduino.h>

void setupInputHandler(int gpio1, int gpio2, int gpio3, int gpio4, xQueueHandle inputQueueHandle);
void taskInputHandler(void *params);

#endif