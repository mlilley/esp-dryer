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
#define HOURS_MIN 0
#define HOURS_MAX 24
#define MINS_MIN 0
#define MINS_MAX 59

// todo :  remove...
#define MIN_TEMP 0
#define MIN_HOURS 0
#define MIN_MINS 0
#define MAX_TEMP 99
#define MAX_HOURS 99
#define MAX_MINS 59

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_OK 2
#define BUTTON_BACK 3

#define ADJUSTVIEW_MODE_TOPOF 0
#define ADJUSTVIEW_MODE_BOTTOMOF 1

typedef struct profile_t {
    const char *name;
    const char *label;
    int hours;
    int mins;
    int temp;
} profile_t;

typedef struct input_t {
    int button;
    bool longpress;
} input_t;

#endif