#include "SelectProfilePage.h"

SelectProfilePage::SelectProfilePage(profile_t profiles[], int nProfiles) {
    m_header = new MenuHeader("Select Profile:");

    MenuItem* items[nProfiles];
    for (int i = 0; i < nProfiles; i++) {
        items[i] = new MenuItem(profiles[i].name);
    }
    m_list = new MenuList(34, 14, 60, 5, items, nProfiles, true); // (128-60)/2 = 34

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

bool SelectProfilePage::handleInput(input_t input) {
    if (m_list->handleInput(input)) {
        m_selected = m_list->getSelected();
        return true;
    }
    switch (input.button) {
        case BUTTON_OK:
            m_accepted = true;
            m_acceptedValue = &m_selected;
            return true;
        case BUTTON_BACK:
            m_cancelled = true;
            return true;
    }
    return false;
}
