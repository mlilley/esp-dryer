#include "ChooseProfilePage.h"

ChooseProfilePage::ChooseProfilePage(ConfigStore* config) : MenuPage(), m_config(config) {
    m_header = new MenuHeader("Choose Profile");

    m_list = new MenuList();
    m_list->setLayout(0, 14, SCREEN_W, 5);
    m_list->setScrollbar(true);
  
    int nProfiles = m_config->getNumProfiles();
    for (int i = 0; i < nProfiles; i++) {
        m_items[i] = new MenuItem(m_config->getProfile(i)->name);
        m_list->addItem(m_items[i]);
    }
}

int ChooseProfilePage::getSelected() {
    return m_list->getSelected();
}

void ChooseProfilePage::activate(bool reset) {
    MenuPage::activate(reset);
    reloadProfiles();
    if (reset) {
        m_list->setSelected(0);
    }
}

void ChooseProfilePage::render(display_t* display) {
    MenuPage::render(display);
    m_header->render(display);
    m_list->render(display);
}

bool ChooseProfilePage::handleInput(input_t* input) {
    if (m_list->handleInput(input)) {
        return true;
    }
    return MenuPage::handleInput(input);
}

void ChooseProfilePage::reloadProfiles(void) {
    int nProfiles = m_config->getNumProfiles();
    for (int i = 0; i < nProfiles; i++) {
        m_items[i]->setTitle(m_config->getProfile(i)->name);
    }
}
