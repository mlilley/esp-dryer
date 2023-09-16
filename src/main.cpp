#include "common.h"
#include "MenuHandler.h"
#include "InputHandler.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define MENU_QUEUE_MSG_A  1
#define MENU_QUEUE_MSG_B  2
#define MENU_QUEUE_MSG_OK 3

Adafruit_SSD1306 display(128, 64, &Wire, -1);

profile_t profiles[] = {
    { .name = "PLA",           .temp = 45, .hours = 60 },
    { .name = "PETG",          .temp = 60, .hours = 60 },
    { .name = "ABS",           .temp = 70, .hours = 60 },
    { .name = "ASA",           .temp = 80, .hours = 60 },
    { .name = "TPU",           .temp = 45, .hours = 40 },
    { .name = "Nylon",         .temp = 80, .hours = 60 },
    { .name = "Polycarbonate", .temp = 80, .hours = 100 },
    { .name = "Custom 1",      .temp = 40, .hours = 240 },
    { .name = "Custom 2",      .temp = 50, .hours = 120 },
    { .name = "Custom 3",      .temp = 60, .hours = 60 },
};

void setup() {
    Serial.begin(9600);
    Wire.begin(GPIO_SDA, GPIO_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println("Screen init failed; halted");
        for (;;);
    }
    display.cp437(true);

    xQueueHandle queueInput = xQueueCreate(100, sizeof(input_t));

    setupMenuHandler(&display, profiles, 10, queueInput);
    setupInputHandler(GPIO_BUTTONUP, GPIO_BUTTONDOWN, GPIO_BUTTONOK, GPIO_BUTTONBACK, queueInput);

    xTaskCreate(taskMenuHandler, "MenuHandler", 5000, NULL, 1, NULL);
    xTaskCreate(taskInputHandler, "InputHandler", 5000, NULL, 1, NULL);
    vTaskDelete(NULL);
}

void loop() {
}
