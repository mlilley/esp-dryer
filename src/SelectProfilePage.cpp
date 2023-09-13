#include "SelectProfilePage.h"

SelectProfilePage::SelectProfilePage(profile_t profiles[], int nProfiles) {
    MenuItem* items[nProfiles];
    for (int i = 0; i < nProfiles; i++) {
        items[i] = new MenuItem(profiles[i].label);
    }

    m_header = new MenuHeader("Select Profile:");
    m_list = new MenuList(0, 14, SCREEN_W, 5, items, nProfiles);
    m_list->selectItem(0);
    m_selected = 0;
}

void SelectProfilePage::activate(bool reset) {
    MenuPage::activate(reset);
    if (reset) {
        m_list->selectItem(0);
        m_selected = 0;
    }
}

void SelectProfilePage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);
    m_header->render(display);
    m_list->render(display);
}

bool SelectProfilePage::handleInput(int button) {
    if (m_list->handleInput(button)) {
        m_selected = m_list->getSelected();
        return true;
    }
    switch (button) {
        case BUTTON_OK:
            m_accepted = true;
            m_acceptedValue = &m_selected;
            return false;
        case BUTTON_BACK:
            m_cancelled = true;
            return false;
    }
    return false;
}
