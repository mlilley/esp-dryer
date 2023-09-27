#ifndef __ESP_DRYER__SETTINGS_PAGE_H__
#define __ESP_DRYER__SETTINGS_PAGE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h" 
#include "message.h"
#include "ConfigStore.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include "MenuItem.h"
#include "UnitsDelegate.h"
#include "MenuDialog.h"
#include "MenuItemClickHandler.h"
#include "MenuDialogCloseHandler.h"

class SettingsPage : public MenuPage {
    protected:
        ConfigStore* m_config;
        MenuHeader* m_header;
        MenuList* m_list;
        MenuItem* m_items[2];
        UnitsDelegate* m_unitsDelegate;
        MenuDialog* m_resetDialog;
        bool m_showResetDialog;

        void onResetClick(void);
        void onResetClose(int result);
        void onUnitsChange(void);
        void refresh(void);

    public:
        SettingsPage(ConfigStore* config);
        void activate(bool reset);
        void render(display_t* display);
        bool handleMsg(msg_t* msg);
};

#endif