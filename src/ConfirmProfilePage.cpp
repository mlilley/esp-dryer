#include "ConfirmProfilePage.h"

#include "MenuEditableIntItem.h"

ConfirmProfilePage::ConfirmProfilePage() {
    MenuItem* items[3];
    items[0] = new MenuEditableIntItem("Temp:", 0, TEMP_MIN, TEMP_MAX);
    items[1] = new MenuEditableIntItem("Hours:", 0, HOURS_MIN, HOURS_MAX);
    items[2] = new MenuEditableIntItem("Minutes:", 0, MINS_MIN, MINS_MAX);

    m_header = new MenuHeader("Confirm Profile:");
    m_list = new MenuList(0, 14, SCREEN_W, 3, items, 3);
}

void ConfirmProfilePage::setProfile(profile_t* profile) {
    ((MenuEditableIntItem*)m_list->getItem(0))->setValue(profile->temp);
    ((MenuEditableIntItem*)m_list->getItem(1))->setValue(profile->hours);
    ((MenuEditableIntItem*)m_list->getItem(2))->setValue(profile->mins);
}

void ConfirmProfilePage::activate(bool reset) {
    MenuPage::activate(reset);
    if (reset) {
        m_list->selectItem(0);
    }
}

void ConfirmProfilePage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);
    m_header->render(display);
    m_list->render(display);
}

bool ConfirmProfilePage::handleInput(int button) {
    if (m_list->handleInput(button)) {
        return true;
    }
    switch (button) {
        case BUTTON_OK:
            m_accepted = true;
            return false;
        case BUTTON_BACK:
            m_cancelled = true;
            return false;
    }
    return false;
}