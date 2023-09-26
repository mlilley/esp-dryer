#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <Arduino.h>
#include "common.h"

typedef struct button_t {
    int gpioPin;
    bool state;
    volatile bool activity;
    bool changing;
    int numConsistentReadings;
    bool lastReading;
    unsigned long lastRead;
} button_t;

class InputTask {
    protected:
        xQueueHandle m_inputQueue;

    public:
        void init(xQueueHandle inputQueue, int gpio1, int gpio2, int gpio3, int gpio4);
        void run(void);

    public:
        static void handler(void* params) {
            ((InputTask*)params)->run();
        }
};

#endif