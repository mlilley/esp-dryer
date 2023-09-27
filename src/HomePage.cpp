#include "HomePage.h"

HomePage::HomePage(ConfigStore* config) : MenuPage(), m_config(config) {
    m_items[0] = new MenuItem("Start");
    m_items[1] = new MenuItem("Settings");

    m_list = new MenuList();
    m_list->setLayout(30, 26, 56, 2);
    m_list->setScrollbar(false);
    m_list->addItem(m_items[0]);
    m_list->addItem(m_items[1]);

    m_temp = 0;
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
    static const int tempCharsWide = 5;
    
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
    if (m_config->getTempUnits() == UNITS_C) {
        display->printf("%.1f\xF8""C", m_temp);
    } else {
        display->printf("%.1f\xF8""F", m_temp * 9.0 / 5.0 + 32);
    }  
    display->fillRect(0, 55, SCREEN_W, 10, INVERSE);

    m_list->render(display);
}

bool HomePage::handleMsg(msg_t* msg) {
    if (m_list->handleMsg(msg)) {
        return true;
    }
    if (IS_SENSOR(msg)) {
        m_temp = msg->temp;
        return true;
    }
    return MenuPage::handleMsg(msg);
}
