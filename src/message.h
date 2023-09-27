#ifndef __ESP_DRYER__MESSAGE_H__
#define __ESP_DRYER__MESSAGE_H__

#define MSG_KIND_INPUT 0
#define MSG_KIND_SENSOR 1

#define IS_INPUT(msg) (msg->kind==MSG_KIND_INPUT)
#define IS_SENSOR(msg) (msg->kind==MSG_KIND_SENSOR)

#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_OK 3
#define BUTTON_BACK 4

typedef struct msg_t {
    int kind;
    int button;
    int longpress;
    float temp;
} input_t;

#endif