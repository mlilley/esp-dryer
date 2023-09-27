#ifndef __ESP_DRYER__SELECT_PROFILE_PAGE_H__
#define __ESP_DRYER__SELECT_PROFILE_PAGE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
#include "ConfigStore.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include "MenuItem.h"

class ChooseProfilePage : public MenuPage {
    protected:
        ConfigStore* m_config;
        MenuHeader* m_header;
        MenuList* m_list;
        MenuItem* m_items[CONFIG_PROFILES_MAX];

    public:
        ChooseProfilePage(ConfigStore* config);
        int getSelected();
        void activate(bool reset);
        virtual void render(display_t* display);
        virtual bool handleMsg(msg_t* msg);

    protected: 
        void reloadProfiles(void);
        void onItemSelect(int index);
        void onItemClick(int index);
};

#endif