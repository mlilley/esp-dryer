#include "MenuHeader.h"

MenuHeader::MenuHeader(const char* title) {
    m_title = title;
}

void MenuHeader::setTitle(const char* title) {
    m_title = title;
}

void MenuHeader::render(Adafruit_SSD1306* display) {
    display->setCursor(0,0);
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->print(m_title);
    display->drawFastHLine(0, H-1, SCREEN_W, SSD1306_WHITE);
}
