#include "MenuHeader.h"

MenuHeader::MenuHeader(const char* title) {
    m_title = title;
}

void MenuHeader::setTitle(const char* title) {
    m_title = title;
}

void MenuHeader::render(Adafruit_SSD1306* display) {
    display->setCursor(2,1);
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->print(m_title);
    display->fillRect(0, 0, SCREEN_W, 10, SSD1306_INVERSE);
}
