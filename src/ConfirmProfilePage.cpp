#include "ConfirmProfilePage.h"

#include "MenuEditableIntItem.h"

ConfirmProfilePage::ConfirmProfilePage() {
    MenuItem* items[6];
    items[0] = new MenuItem("START");
    items[1] = new MenuEditableIntItem("Temp", 0, TEMP_MIN, TEMP_MAX, 2);
    items[2] = new MenuEditableIntItem("Hours", 0, HOURS_MIN, HOURS_MAX, 2);
    items[3] = new MenuEditableIntItem("Minutes", 0, MINS_MIN, MINS_MAX, 2);
    items[4] = new MenuItem("Save");
    items[5] = new MenuItem("Reset");

    m_header = new MenuHeader("Confirm Profile:");
    // 11 chars + 1 => 72px => (128-72)/2 => 28px
    m_list = new MenuList(28, 14, 72, 5, items, 6);
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

bool ConfirmProfilePage::handleInput(input_t input) {
    if (m_list->handleInput(input)) {
        return true;
    }
    switch (input.button) {
        case BUTTON_OK:
            m_accepted = true;
            return false;
        case BUTTON_BACK:
            m_cancelled = true;
            return false;
    }
    return false;
}