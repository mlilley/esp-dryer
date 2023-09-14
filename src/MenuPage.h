#ifndef __MENU_PAGE_H__
#define __MENU_PAGE_H__

#include "common.h"
#include <Adafruit_SSD1306.h>

class MenuPage {
    protected:
        bool m_accepted;
        bool m_cancelled;
        void* m_acceptedValue;
    public:
        MenuPage();
        bool isAccepted();
        bool isCancelled();
        virtual void activate(bool reset);
        void* getAcceptedValue();
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
};

#endif