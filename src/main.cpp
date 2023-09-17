#include "common.h"
#include "ConfigStore.h"
#include "MenuHandler.h"
#include "InputHandler.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define MENU_QUEUE_MSG_A  1
#define MENU_QUEUE_MSG_B  2
#define MENU_QUEUE_MSG_OK 3

Adafruit_SSD1306 display(128, 64, &Wire, -1);

static ConfigStore config = ConfigStore();

void setup() {
    Serial.begin(9600);
    Wire.begin(GPIO_SDA, GPIO_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println("Screen init failed; halted");
        for (;;);
    }
    display.cp437(true);

    config.load();

    xQueueHandle queueInput = xQueueCreate(100, sizeof(input_t));

    setupMenuHandler(&config, queueInput, &display);
    setupInputHandler(GPIO_BUTTONUP, GPIO_BUTTONDOWN, GPIO_BUTTONOK, GPIO_BUTTONBACK, queueInput);

    xTaskCreate(taskMenuHandler, "MenuHandler", 5000, NULL, 1, NULL);
    xTaskCreate(taskInputHandler, "InputHandler", 5000, NULL, 1, NULL);
    vTaskDelete(NULL);
}

void loop() {
}
