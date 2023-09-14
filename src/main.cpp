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
    { .name = "PLA",   .label = "PLA ..... 6h @ 45""\xF8""C", .hours = 6,  .mins = 0, .temp = 45 },
    { .name = "PETG",  .label = "PETG .... 6h @ 60""\xF8""C", .hours = 6,  .mins = 0, .temp = 60 },
    { .name = "ABS",   .label = "ABS ..... 6h @ 70""\xF8""C", .hours = 6,  .mins = 0, .temp = 70 },
    { .name = "ASA",   .label = "ASA ..... 6h @ 80""\xF8""C", .hours = 6,  .mins = 0, .temp = 80 },
    { .name = "TPU",   .label = "TPU ..... 4h @ 45""\xF8""C", .hours = 4,  .mins = 0, .temp = 45 },
    { .name = "Nylon", .label = "Nylon ... 6h @ 80""\xF8""C", .hours = 6,  .mins = 0, .temp = 80 },
    { .name = "PolyC", .label = "PolyC .. 10h @ 80""\xF8""C", .hours = 10, .mins = 0, .temp = 80 } 
};

void setup() {
    Serial.begin(9600);
    Wire.begin(GPIO_SDA, GPIO_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println("Screen init failed; halted");
        for (;;);
    }
    display.cp437(true);

    Serial.print("OK");

    xQueueHandle queueInput = xQueueCreate(100, sizeof(input_t));

    setupMenuHandler(&display, profiles, 7, queueInput);
    setupInputHandler(GPIO_BUTTONUP, GPIO_BUTTONDOWN, GPIO_BUTTONOK, GPIO_BUTTONBACK, queueInput);

    xTaskCreate(taskMenuHandler, "MenuHandler", 5000, NULL, 1, NULL);
    xTaskCreate(taskInputHandler, "InputHandler", 5000, NULL, 1, NULL);
    vTaskDelete(NULL);
}

void loop() {
}
