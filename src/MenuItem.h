#ifndef __ESP_DRYER__MENU_ITEM_H__
#define __ESP_DRYER__MENU_ITEM_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
#include "MenuItemClickHandler.h"

class MenuItem {
    protected:
        const char* m_title;
        bool m_selected;
        IMenuItemClickHandler* m_onClick;

    public:
        MenuItem();
        MenuItem(const char* title);
        void setTitle(const char* title);
        void setSelected(bool selected);
        void onClick(IMenuItemClickHandler* onClick);

        virtual void render(display_t* display, int x, int y, int w, int h);
        virtual bool handleMsg(msg_t* msg);
};

#endif