#ifndef __CONFIRM_PROFILE_PAGE_H__
#define __CONFIRM_PROFILE_PAGE_H__

#include "common.h"
#include "MenuPage.h"
#include "MenuHeader.h"
#include "MenuList.h"
#include "MenuDialog.h"
#include <Adafruit_SSD1306.h>

class ConfirmProfilePage : public MenuPage {
    protected:
        MenuHeader* m_header;
        MenuList* m_list;
        MenuDialog* m_saveDialog;
        MenuDialog* m_resetDialog;
        profile_t* m_profile;
        bool m_showSaveDialog;
        bool m_showResetDialog;
    public:
        ConfirmProfilePage();
        void setProfile(profile_t* profile);
        void activate(bool reset);
        virtual void render(Adafruit_SSD1306* display);
        virtual bool handleInput(input_t input);
};

#endif