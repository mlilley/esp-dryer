#ifndef __MENU_HANDLER_H__
#define __MENU_HANDLER_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "ConfigStore.h"
#include "HomePage.h"
#include "ChooseProfilePage.h"
#include "ConfirmProfilePage.h"
#include "SettingsPage.h"

class MenuTask {
    protected:
        ConfigStore* m_config;

        HomePage* m_homePage;
        ChooseProfilePage* m_chooseProfilePage;
        ConfirmProfilePage* m_confirmProfilePage;
        SettingsPage* m_settingsPage;
        MenuPage* m_currentPage;

        display_t* m_display;
        xQueueHandle m_inputQueue;

    protected:
        void onHomePageComplete(int result);
        void onChooseProfilePageComplete(int result);
        void onConfirmProfilePageComplete(int result);
        void onSettingsPageComplete(int result);
        void render();

    public:
        void init(ConfigStore* config, display_t* display, xQueueHandle inputQueue);
        void run(void);

    public:
        static void handler(void* params) {
            ((MenuTask*)params)->run();
        }
};

#endif