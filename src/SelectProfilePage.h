#ifndef __SELECT_PROFILE_PAGE_H__
#define __SELECT_PROFILE_PAGE_H__

#include "common.h"
#include "ConfigStore.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include <Adafruit_SSD1306.h>

class SelectProfilePage : public MenuPage {
    protected:
        ConfigStore* m_pConfig;
        MenuHeader m_header;
        MenuList m_list;
        MenuItem* m_items[CONFIG_PROFILES_MAX];
    protected:
        int m_value;
    public:
        SelectProfilePage(ConfigStore* pConfig);
        void activate(bool reset);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
};

#endif