#include "MenuItem.h"

MenuItem::MenuItem(const char* title) {
    m_title = title;
    m_selected = false;
}

void MenuItem::setTitle(const char* title) {
    m_title = title;
}

void MenuItem::setSelected(bool selected) {
    m_selected = selected;
}

void MenuItem::render(Adafruit_SSD1306* display, int x, int y, int w) {
    display->setTextColor(SSD1306_WHITE);
    if (m_selected) {
        display->setCursor(x, y);
        display->print("\x10");
    }
    display->setCursor(x+8, y);
    display->printf("%s",(m_title == NULL ? "" : m_title));
}

bool MenuItem::handleInput(input_t input) {
    return false;
}