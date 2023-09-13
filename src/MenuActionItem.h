#ifndef __MENU_ACTION_ITEM_H__
#define __MENU_ACTION_ITEM_H__

#include "common.h"
#include "MenuItem.h"
#include <Adafruit_SSD1306.h>

class MenuActionItem : public MenuItem {
    public:
        MenuActionItem();
        virtual void render(Adafruit_SSD1306* display, int y);
        virtual bool onButton(int button);
};

#endif