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
    display->setCursor(0, y);
    display->setTextColor(SSD1306_WHITE);
    display->printf((m_selected ? ">%s" : " %s"), (m_title == NULL ? "" : m_title));
}

bool MenuItem::handleInput(int button) {
    return false;
}