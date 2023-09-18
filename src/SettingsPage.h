#ifndef __SETTINGS_PAGE_H__
#define __SETTINGS_PAGE_H__

#include "common.h"
#include "ConfigStore.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include "MenuEditableTempUnitsItem.h"
#include "MenuDialog.h"
#include <Adafruit_SSD1306.h> 

class SettingsPage : public MenuPage {
    protected:
        ConfigStore* m_pConfig;
        MenuHeader m_header;
        MenuList m_list;
        MenuItem* m_items[5];
        MenuDialog m_resetDialog;
        bool m_showResetDialog;

    protected:
        void refresh();

    public:
        SettingsPage(ConfigStore* pConfig);
        void activate(bool reset);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
        void onTempUnitChange();
};

#endif