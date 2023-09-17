#ifndef __CONFIRM_PROFILE_PAGE_H__
#define __CONFIRM_PROFILE_PAGE_H__

#include "common.h"
#include "ConfigStore.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include "MenuDialog.h"
#include <Adafruit_SSD1306.h>

class ConfirmProfilePage : public MenuPage {
    protected:
        ConfigStore* m_pConfig;
        MenuHeader m_header;
        MenuItem* m_items[CONFIG_PROFILES_MAX];
        MenuList m_list;
        MenuDialog m_saveDialog;
        MenuDialog m_resetDialog;

        int m_profile;
        bool m_showSaveDialog;
        bool m_showResetDialog;
    public:
        ConfirmProfilePage(ConfigStore* config);
        void setProfile(int index);
        void activate(bool reset);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
};

#endif