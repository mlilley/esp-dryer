#ifndef __SELECT_PROFILE_PAGE_H__
#define __SELECT_PROFILE_PAGE_H__

#include "common.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include <Adafruit_SSD1306.h>

class SelectProfilePage : public MenuPage {
    protected:
        MenuHeader* m_header;
        MenuList* m_list;
        int m_selected;
    public:
        SelectProfilePage(profile_t profiles[], int nProfiles);
        void activate(bool reset);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
};

#endif