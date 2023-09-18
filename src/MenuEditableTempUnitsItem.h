#ifndef __MENU_EDITABLE_TEMP_UNITS_ITEM_H__
#define __MENU_EDITABLE_TEMP_UNITS_ITEM_H__

#include "common.h"
#include "MenuEditableItem.h"
#include <Adafruit_SSD1306.h>

class MenuEditableTempUnitsItem : public MenuEditableItem {
    public:
        static const int UNITS_C = 0;
        static const int UNITS_F = 1;
    protected:
        int m_value;
        int m_prevValue;
    public:
        MenuEditableTempUnitsItem(const char* title, int value);
        void setTitle(const char* title);
        void setValue(int value);
        int getValue();
        virtual void render(Adafruit_SSD1306* display, int x, int y, int w);
        virtual bool handleInput(input_t input);
};

#endif