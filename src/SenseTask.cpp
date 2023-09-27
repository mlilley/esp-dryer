#include "SenseTask.h"

void SenseTask::init(xQueueHandle msgQueue) {
    m_msgQueue = msgQueue;

    OneWire oneWire(GPIO_TEMP);
    m_sensors = DallasTemperature(&oneWire);
    m_sensors.begin();
    if (m_sensors.getDeviceCount() != 1) {
        Serial.print("Failed to init temp sensor\n");
        for (;;) {}
    }
    m_sensors.getAddress(m_sensor1, 0);
    m_sensors.setResolution(m_sensor1, SENSOR_RESOLUTION);
}

void SenseTask::run(void) {
    const TickType_t delay = READ_INTERVAL_MS / portTICK_PERIOD_MS;

    msg_t msg;
    msg.kind = MSG_KIND_SENSOR;
    
    for (;;) {
        m_sensors.requestTemperatures();
        msg.temp = m_sensors.getTempC(m_sensor1);
        xQueueSend(m_msgQueue, &msg, 500);

        Serial.printf("Temp: %f\n", msg.temp);
        vTaskDelay(delay);
    }
}
