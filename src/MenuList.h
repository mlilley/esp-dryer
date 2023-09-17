#ifndef __MENU_LIST_H__
#define __MENU_LIST_H__

#include "common.h"
#include "ConfigStore.h"
#include "MenuItem.h"

class MenuList {
    protected:
        static const int ITEMS_MAX = CONFIG_PROFILES_MAX;

    protected:
        int m_x;
        int m_y;
        int m_w;
        int m_h;
        int m_nLines;
        int m_scrollbarEnabled;
        MenuItem* m_items[ITEMS_MAX];
        int m_nItems;
        int m_selected;
        int m_viewFirst;

    public:
        MenuList();
        MenuList(int x, int y, int w, int lines, MenuItem* items[], int nItems, bool indicator);
        void setLayout(int x, int y, int w, int lines);
        void setScrollbarEnabled(bool enabled);
        void setItems(MenuItem* items[], int nItems);
        void setSelected(int item);
        int getSelected();
        MenuItem* getItem(int item);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);

    protected:
        void selectPrev();
        void selectNext();
        void adjustView();
        void adjustSelected();
};

#endif