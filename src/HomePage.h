#ifndef __HOME_PAGE_H__
#define __HOME_PAGE_H__

#include "common.h"
#include "MenuPage.h"
#include "MenuList.h"
#include <Adafruit_SSD1306.h>

class HomePage : public MenuPage {
    protected:
        MenuList* m_list;
        int m_selected;
    public:
        HomePage();
        void activate(bool reset);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
};

#endif