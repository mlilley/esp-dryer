#ifndef __MENU_HEADER_H__
#define __MENU_HEADER_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"

class MenuHeader {
    protected:
        static const int H = 10;

        const char* m_title;

    public:
        MenuHeader();
        MenuHeader(const char* title);
        void setTitle(const char* title);
        virtual void render(display_t* display);

};

#endif