#ifndef __MENU_LIST_H__
#define __MENU_LIST_H__

#include "common.h"
#include "MenuItem.h"

class MenuList {
    protected:
        int m_x;
        int m_y;
        int m_w;
        int m_h;
        int m_lines;
        MenuItem* m_items[MENUITEMS_MAX];
        int m_nItems;
        int m_selected;
        int m_viewFirst;

    public:
        MenuList(int x, int y, int w, int lines, MenuItem* items[], int nItems);
        void selectItem(int item);
        int getSelected();
        MenuItem* getItem(int item);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);

    protected:
        void selectPrev();
        void selectNext();
        void adjustView(int mode);
};

#endif