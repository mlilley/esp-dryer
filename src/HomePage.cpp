#include "HomePage.h"

#include "MenuPage.h"
#include <Adafruit_SSD1306.h>

HomePage::HomePage() : MenuPage() {
    MenuItem* items[2];
    items[0] = new MenuItem("START");
    items[1] = new MenuItem("SETTINGS");
    m_list = new MenuList(30, 26, 56, 2, items, 2, false);
}

void HomePage::activate(bool reset) {
    MenuPage::activate(reset);
    if (reset) {
        m_list->selectItem(0);
        m_selected = 0;
    }
}

void HomePage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);

    display->setTextColor(SSD1306_WHITE);
    display->setTextSize(2);
    display->setCursor(12,1);
    display->print("ESP-DRYER");
    display->fillRect(0, 0, SCREEN_W, 16, SSD1306_INVERSE);

    display->setTextSize(1);
    display->setCursor(2, 56);
    display->printf("v%s", VERSION);
    display->setCursor(102, 56);
    display->printf("%*d\xF8""C", 2, 45);
    display->fillRect(0, 55, SCREEN_W, 10, SSD1306_INVERSE);

    m_list->render(display);
}

bool HomePage::handleInput(input_t input) {
    if (m_list->handleInput(input)) {
        m_selected = m_list->getSelected();
        return true;
    }
    switch (input.button) {
        case BUTTON_OK:
            m_accepted = true;
            m_acceptedValue = &m_selected;
            return true;
    }
    return false;
}
