#ifndef __ESP_DRYER__SENSE_TASK_H__
#define __ESP_DRYER__SENSE_TASK_H__

#include <Arduino.h>
#include <DallasTemperature.h>
#include "common.h"
#include "message.h"

class SenseTask {
    protected:
        static const int READ_INTERVAL_MS = 5 * 1000;
        static const uint8_t SENSOR_RESOLUTION = 12;

        xQueueHandle m_msgQueue;
        DallasTemperature m_sensors;
        DeviceAddress m_sensor1;

    public:
        void init(xQueueHandle msgQueue);
        void run(void);

    public:
        static void handler(void* params) {
            ((SenseTask*)params)->run();
        }
};

#endif