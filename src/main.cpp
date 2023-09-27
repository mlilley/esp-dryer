#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"
#include "display.h"
#include "ConfigStore.h"
#include "MenuTask.h"
#include "InputTask.h"
#include "SenseTask.h"

#define MENU_QUEUE_MSG_A  1
#define MENU_QUEUE_MSG_B  2
#define MENU_QUEUE_MSG_OK 3

static display_t display(128, 64, &Wire, -1);
static ConfigStore config = ConfigStore();

static MenuTask menuTask;
static InputTask inputTask;
static SenseTask senseTask;

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

    xQueueHandle msgQueue = xQueueCreate(100, sizeof(msg_t));

    menuTask.init(&config, &display, msgQueue);
    inputTask.init(msgQueue, GPIO_BUTTONUP, GPIO_BUTTONDOWN, GPIO_BUTTONOK, GPIO_BUTTONBACK);
    senseTask.init(msgQueue);
    
    xTaskCreate(MenuTask::handler, "MenuTask", 5000, &menuTask, 1, NULL);
    xTaskCreate(InputTask::handler, "InputTask", 5000, &inputTask, 1, NULL);
    xTaskCreate(SenseTask::handler, "SenseTask", 5000, &senseTask, 1, NULL);
    vTaskDelete(NULL);
}

void loop() { }
