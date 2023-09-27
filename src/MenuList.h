#ifndef __ESP_DRYER__MENU_LIST_H__
#define __ESP_DRYER__MENU_LIST_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
#include "ConfigStore.h"
#include "MenuItem.h"
#include "MenuListItemSelectHandler.h"
#include "MenuListItemClickHandler.h"

class MenuList {
    protected:
        static const int ITEMS_MAX = CONFIG_PROFILES_MAX;
        static const int ITEM_H = 10;

        MenuItem* m_items[ITEMS_MAX];
        int m_nItems;
        int m_x;
        int m_y;
        int m_w;
        int m_h;
        int m_nLines;
        int m_scrollbar;
        int m_selected;
        int m_viewFirst;
        IMenuListItemSelectHandler* m_onSelect;
        IMenuListItemClickHandler* m_onClick;

        void selectPrev();
        void selectNext();
        void adjustView();
        void adjustSelected();

    public:
        MenuList();

        int addItem(MenuItem* item);
        void setLayout(int x, int y, int w, int lines);
        void setScrollbar(bool enabled);
        void setSelected(int item);
        int getSelected();
        MenuItem* getItem(int item);
        void onItemSelect(IMenuListItemSelectHandler* onSelect);
        void onItemClick(IMenuListItemClickHandler* onClick);

        virtual void render(display_t* display);
        virtual bool handleMsg(msg_t* msg);
};

#endif