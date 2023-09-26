#include "HomePage.h"

HomePage::HomePage(ConfigStore* config) : MenuPage(), m_config(config) {
    m_items[0] = new MenuItem("Start");
    m_items[1] = new MenuItem("Settings");

    m_list = new MenuList();
    m_list->setLayout(30, 26, 56, 2);
    m_list->setScrollbar(false);
    m_list->addItem(m_items[0]);
    m_list->addItem(m_items[1]);
}

void HomePage::activate(bool reset) {
    MenuPage::activate(reset);
    if (reset) {
        m_list->setSelected(0);
    }
}

int HomePage::getSelected() {
    return m_list->getSelected();
}

void HomePage::render(display_t* display) {
    MenuPage::render(display);

    display->setTextColor(WHITE);
    display->setTextSize(2);
    display->setCursor(18,1);
    display->print("ESPiDRY");
    display->fillRect(0, 0, SCREEN_W, 16, INVERSE);

    display->setTextSize(1);
    display->setCursor(2, 56);
    display->printf("v%s", VERSION);
    display->setCursor(102, 56);
    display->printf("%*d\xF8""C", 2, 45);
    display->fillRect(0, 55, SCREEN_W, 10, INVERSE);

    m_list->render(display);
}

bool HomePage::handleInput(input_t* input) {
    if (m_list->handleInput(input)) {
        return true;
    }
    return MenuPage::handleInput(input);
}
