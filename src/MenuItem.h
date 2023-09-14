#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include "common.h"
#include <Adafruit_SSD1306.h>

class MenuItem {
    public:
        static const int H = 10;
    protected:
        const char* m_title;
        bool m_selected;
    public:
        MenuItem(const char* title);
        void setTitle(const char* title);
        void setSelected(bool selected);
        virtual void render(Adafruit_SSD1306* display, int x, int y, int w);
        virtual bool handleInput(input_t input);
};

#endif