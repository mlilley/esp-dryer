#ifndef __MENU_EDITABLE_INT_ITEM_H__
#define __MENU_EDITABLE_INT_ITEM_H__

#include "common.h"
#include "MenuEditableItem.h"
#include <Adafruit_SSD1306.h>

class MenuEditableIntItem : public MenuEditableItem {
    protected:
        int m_value;
        int m_prevValue;
        int m_min;
        int m_max;
        int m_chars;
    public:
        MenuEditableIntItem(const char* title, int value, int min, int max, int chars);
        int getValue();
        void setValue(int value);
        virtual void render(Adafruit_SSD1306* display, int x, int y, int w);
        virtual bool handleInput(input_t input);
};

#endif