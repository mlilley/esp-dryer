#include "MenuHeader.h"

MenuHeader::MenuHeader() {
    m_title = "";
}

MenuHeader::MenuHeader(const char* title) {
    m_title = title;
}

void MenuHeader::setTitle(const char* title) {
    m_title = title;
}

void MenuHeader::render(display_t* display) {
    display->setCursor(2,1);
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->print(m_title);
    display->fillRect(0, 0, SCREEN_W, 10, INVERSE);
}
