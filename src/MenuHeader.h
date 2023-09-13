#ifndef __MENU_HEADER_H__
#define __MENU_HEADER_H__

#include "common.h"
#include <Adafruit_SSD1306.h>

class MenuHeader {
    protected:
        static const int H = 10;
    protected:
        const char* m_title;
    public:
        MenuHeader(const char* title);
        void setTitle(const char* title);
        virtual void render(Adafruit_SSD1306* display);
};

#endif