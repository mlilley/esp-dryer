#include <Arduino.h>
#include <Wire.h>
#include "common.h"
#include "display.h"
#include "ConfigStore.h"
#include "MenuTask.h"
#include "InputTask.h"

#define MENU_QUEUE_MSG_A  1
#define MENU_QUEUE_MSG_B  2
#define MENU_QUEUE_MSG_OK 3

static display_t display(128, 64, &Wire, -1);
static ConfigStore config = ConfigStore();

static MenuTask menuTask;
static InputTask inputTask;

void setup() {
    Serial.begin(9600);
    Wire.begin(GPIO_SDA, GPIO_SCL);

    if (!display.begin(SH1106_SWITCHCAPVCC, 0x3c)) {
        Serial.println("Screen init failed; halted");
        for (;;);
    }
    display.cp437(true);
    display.clearDisplay();
    display.display();

    config.load();

    xQueueHandle queueInput = xQueueCreate(100, sizeof(input_t));

    menuTask.init(&config, &display, queueInput);
    inputTask.init(queueInput, GPIO_BUTTONUP, GPIO_BUTTONDOWN, GPIO_BUTTONOK, GPIO_BUTTONBACK);
    
    xTaskCreate(MenuTask::handler, "MenuTask", 5000, &menuTask, 1, NULL);
    xTaskCreate(InputTask::handler, "InputTask", 5000, &inputTask, 1, NULL);
    vTaskDelete(NULL);
}

void loop() {
}
