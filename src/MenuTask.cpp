#include "MenuTask.h"

void MenuTask::init(ConfigStore* config, display_t* display, xQueueHandle msgQueue) {
    m_config = config;
    m_display = display;
    m_msgQueue = msgQueue;

    m_homePage = new HomePage(m_config);
    m_homePage->onComplete(new MenuPageCompletionHandler<MenuTask>(this, &MenuTask::onHomePageComplete));

    m_chooseProfilePage = new ChooseProfilePage(m_config);
    m_chooseProfilePage->onComplete(new MenuPageCompletionHandler<MenuTask>(this, &MenuTask::onChooseProfilePageComplete));

    m_confirmProfilePage = new ConfirmProfilePage(m_config);
    m_confirmProfilePage->onComplete(new MenuPageCompletionHandler<MenuTask>(this, &MenuTask::onConfirmProfilePageComplete));
    
    m_settingsPage = new SettingsPage(m_config);
    m_settingsPage->onComplete(new MenuPageCompletionHandler<MenuTask>(this, &MenuTask::onSettingsPageComplete));

    m_currentPage = m_homePage;
}

void MenuTask::run(void) {
    msg_t msg;

    m_currentPage->activate(true);
    m_currentPage->render(m_display);
    m_display->display();

    for (;;) {
        if (xQueueReceive(m_msgQueue, &msg, 500)) {
            if (m_currentPage->handleMsg(&msg)) {
                m_currentPage->render(m_display);
                m_display->display();
            }
        }
    }
}

void MenuTask::onHomePageComplete(int result)  {
    if (result == 1) { // ok
        switch (m_homePage->getSelected()) {
            case 0: // Start
                m_currentPage = m_chooseProfilePage;
                m_chooseProfilePage->activate(true);
                break;
            case 1: // Settings
                m_currentPage = m_settingsPage;
                m_settingsPage->activate(true);
                break;
        }
    }
}

void MenuTask::onChooseProfilePageComplete(int result) {
    if (result == MENU_PAGE_RESULT_OK) {
        m_currentPage = m_confirmProfilePage;
        m_confirmProfilePage->setProfile(m_chooseProfilePage->getSelected());
        m_confirmProfilePage->activate(true);
    } else if (result == MENU_PAGE_RESULT_BACK) {
        m_currentPage = m_homePage;
        m_homePage->activate(true);
    }
}

void MenuTask::onConfirmProfilePageComplete(int result) {
    if (result == MENU_PAGE_RESULT_OK) {
        profile_t profile = m_confirmProfilePage->getConfirmedProfile();
    } else if (result == MENU_PAGE_RESULT_BACK) {
        m_currentPage = m_chooseProfilePage;
        m_chooseProfilePage->activate(false);
    }
}

void MenuTask::onSettingsPageComplete(int result) {
    m_currentPage = m_homePage;
    m_homePage->activate(false);
}
