#ifndef __ESP_DRYER__MENU_TASK_H__
#define __ESP_DRYER__MENU_TASK_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
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
        xQueueHandle m_msgQueue;

    protected:
        void onHomePageComplete(int result);
        void onChooseProfilePageComplete(int result);
        void onConfirmProfilePageComplete(int result);
        void onSettingsPageComplete(int result);
        void render();

    public:
        void init(ConfigStore* config, display_t* display, xQueueHandle msgQueue);
        void run(void);

    public:
        static void handler(void* params) {
            ((MenuTask*)params)->run();
        }
};

#endif