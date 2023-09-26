#ifndef __HOME_PAGE_H__
#define __HOME_PAGE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "MenuPage.h"
#include "MenuList.h"
#include "MenuItem.h"

class HomePage : public MenuPage {
    protected:
        ConfigStore* m_config;
        MenuList* m_list;
        MenuItem* m_items[2];

    public:
        HomePage(ConfigStore* config);
        void activate(bool reset);
        int getSelected();
        virtual void render(display_t* display);
        virtual bool handleInput(input_t* input);

};

#endif