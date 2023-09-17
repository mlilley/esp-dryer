#include "SelectProfilePage.h"

SelectProfilePage::SelectProfilePage(ConfigStore* pConfig) 
        : m_header(), m_list(), m_items{} {
    m_pConfig = pConfig;
    m_header.setTitle("Select Profile");
    
    int nProfiles = m_pConfig->getNumProfiles();
    for (int i = 0; i < nProfiles; i++) {
        m_items[i] = new MenuItem(pConfig->getProfile(i)->name);
    }

    m_list.setLayout(0, 14, SCREEN_W, 5);
    m_list.setScrollbarEnabled(true);
    m_list.setItems(m_items, nProfiles);
}

void SelectProfilePage::activate(bool reset) {
    MenuPage::activate(reset);
    if (reset) {
        m_list.setSelected(0);
    }
}

void SelectProfilePage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);
    m_header.render(display);
    m_list.render(display);
}

bool SelectProfilePage::handleInput(input_t input) {
    if (m_list.handleInput(input)) {
        return true;
    }
    switch (input.button) {
        case BUTTON_OK:
            m_accepted = true;
            m_value = m_list.getSelected();
            m_acceptedValue = &m_value;
            return true;
        case BUTTON_BACK:
            m_cancelled = true;
            return true;
    }
    return false;
}
