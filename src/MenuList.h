#ifndef __MENU_LIST_H__
#define __MENU_LIST_H__

#include "common.h"
#include "MenuItem.h"

class MenuList {
    protected:
        static const int ADJUSTVIEW_MODE_TOPOF = 0;
        static const int ADJUSTVIEW_MODE_BOTTOMOF = 1;

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
        int m_indicator;

    public:
        MenuList(int x, int y, int w, int lines, MenuItem* items[], int nItems, bool indicator);
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