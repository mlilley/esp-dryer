#ifndef __MENU_EDITABLE_ITEM_H__
#define __MENU_EDITABLE_ITEM_H__

#include "common.h"
#include "MenuItem.h"
#include <Adafruit_SSD1306.h>

class MenuEditableItem : public MenuItem {
    protected:
        bool m_editing;
        onChange_t m_onChange;
        void* m_onChangeMethodInstance;

    public:
        MenuEditableItem(const char* title);
        void setChangeHandler(onChange_t handler, void* methodInstance);
        virtual void render(Adafruit_SSD1306* display, int x, int y, int w);
        virtual bool handleInput(input_t input);
};

#endif