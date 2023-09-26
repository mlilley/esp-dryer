#ifndef __COMMON_H__
#define __COMMON_H__

#define VERSION "1.0"

#define GPIO_SDA 21
#define GPIO_SCL 22

#define GPIO_BUTTONUP 18
#define GPIO_BUTTONDOWN 19
#define GPIO_BUTTONOK 23
#define GPIO_BUTTONBACK 32

#define SCREEN_W 128
#define SCREEN_H 64

#define MENUITEMS_MAX 10

#define TEMP_MIN 0
#define TEMP_MAX 80
#define HOURS_MIN 1800 // seconds
#define HOURS_MAX 86400 // seconds

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_OK 2
#define BUTTON_BACK 3

#define UNITS_C 0
#define UNITS_F 1

typedef struct input_t {
    int button;
    bool longpress;
} input_t;

#endif