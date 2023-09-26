#ifndef __CONFIRM_PROFILE_PAGE_H__
#define __CONFIRM_PROFILE_PAGE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "profile.h"
#include "ConfigStore.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include "MenuItem.h"
#include "MenuEditableItem.h"
#include "TempDelegate.h"
#include "HoursDelegate.h"
#include "MenuDialog.h"

class ConfirmProfilePage : public MenuPage {
    protected:
        ConfigStore* m_config;
        MenuHeader* m_header;
        MenuItem* m_items[5];
        MenuList* m_list;
        MenuDialog* m_saveDialog;
        MenuDialog* m_resetDialog;
        int m_profile;
        bool m_showSaveDialog;
        bool m_showResetDialog;

        void onStartClick(void);
        void onSaveClick(void);
        void onResetClick(void);
        void onSaveDialogClose(int result);
        void onResetDialogClose(int result);

    public:
        ConfirmProfilePage(ConfigStore* config);

        void activate(bool reset);
        void setProfile(int index);
        profile_t getConfirmedProfile(void);
        virtual void render(display_t* display);
        virtual bool handleInput(input_t* input);
};

#endif