#include "InputHandler.h"

#define NUM_BUTTONS 4
#define BTN_NUM_REQUIRED_CONSISTENT_READINGS 5
#define BTN_QUIESCENCE 10
#define BTN_REPEAT 500

typedef struct button_t {
    int gpioPin;
    bool state;
    volatile bool activity;
    bool changing;
    int numConsistentReadings;
    bool lastReading;
    unsigned long lastRead;
} button_t;

void IRAM_ATTR isrButton1();
void IRAM_ATTR isrButton2();
void IRAM_ATTR isrButton3();
void IRAM_ATTR isrButton4();

static button_t buttons[NUM_BUTTONS];
static xQueueHandle queueInput;

void setupInputHandler(int gpio1, int gpio2, int gpio3, int gpio4, xQueueHandle inputQueueHandle) {
    buttons[0].gpioPin = gpio1;
    buttons[1].gpioPin = gpio2;
    buttons[2].gpioPin = gpio3;
    buttons[3].gpioPin = gpio4;

    queueInput = inputQueueHandle;

    pinMode(buttons[0].gpioPin, INPUT_PULLUP);
    pinMode(buttons[1].gpioPin, INPUT_PULLUP);
    pinMode(buttons[2].gpioPin, INPUT_PULLUP);
    pinMode(buttons[3].gpioPin, INPUT_PULLUP);

    attachInterrupt(buttons[0].gpioPin, isrButton1, CHANGE);
    attachInterrupt(buttons[1].gpioPin, isrButton2, CHANGE);
    attachInterrupt(buttons[2].gpioPin, isrButton3, CHANGE);
    attachInterrupt(buttons[3].gpioPin, isrButton4, CHANGE);
}

/**
 * Handler debounces button activity by looking for multiple consecutive 
 * consistent readings, prior to recording the button as changing state.
 * Button presses are placed in a queue, for consumption by other tasks.
 * Holding a button down results in repeat button presses, and applying the 
 * long-press modifer;
 */
void taskInputHandler(void *param) {
    const TickType_t delay = 2/portTICK_PERIOD_MS;
    bool reading;
    input_t input;
    for (;;) {
        for (int x = 0; x < NUM_BUTTONS; x++) {
            if (!buttons[x].changing) {
                if (buttons[x].activity) {
                    // Button is not currently changing, and ISR has indicated a change,
                    // initiate changing mode and take a reading.
                    buttons[x].activity = false;
                    buttons[x].changing = true;
                    buttons[x].numConsistentReadings = 0;
                    buttons[x].lastReading = digitalRead(buttons[x].gpioPin) == 0;
                    buttons[x].lastRead = millis();
                } else if (buttons[x].state) {
                    // Button is pushed (and not changing).
                    unsigned long ms = millis();
                    if (ms - buttons[x].lastRead > BTN_REPEAT) {
                        // Button has remained pushed for the repeat period; enqueue another pushed msg.
                        buttons[x].lastRead = ms;
                        input.button = x;
                        input.longpress = true;
                        xQueueSend(queueInput, &input, 500);
                    }
                }
            } else {
                // Button is changing. Test button for x consistent reads every y milliseconds.
                unsigned long ms = millis();
                if (ms - buttons[x].lastRead > BTN_QUIESCENCE) {
                    reading = digitalRead(buttons[x].gpioPin) == 0;
                    buttons[x].lastRead = ms;
                    if (reading == buttons[x].lastReading) {
                        // This as last readings are consistent; increment number of required consistent readings.
                        buttons[x].numConsistentReadings++;
                        if (buttons[x].numConsistentReadings >= BTN_NUM_REQUIRED_CONSISTENT_READINGS) {
                            // Last x reads were all consistent; consider button state changed.
                            buttons[x].state = reading;
                            buttons[x].changing = false;
                            buttons[x].numConsistentReadings = 0;
                            // If button changed to pushed, enqueue a pushed msg.
                            if (buttons[x].state) {
                                input.button = x;
                                input.longpress = false;
                                xQueueSend(queueInput, &input, 500);
                            }              
                        }
                    } else {
                        // During changing mode, we got an inconsistent reading. Reset
                        // any consistent reads received so far and start over.
                        buttons[x].numConsistentReadings = 0;
                        buttons[x].lastReading = reading;
                    }
                }
            }
        }
        vTaskDelay(delay);
    }
}

void IRAM_ATTR isrButton1() {
    buttons[0].activity = true;
}

void IRAM_ATTR isrButton2() {
    buttons[1].activity = true;
}

void IRAM_ATTR isrButton3() {
    buttons[2].activity = true;
}

void IRAM_ATTR isrButton4() {
    buttons[3].activity = true;
}
