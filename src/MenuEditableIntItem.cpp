#include "MenuEditableIntItem.h"

MenuEditableIntItem::MenuEditableIntItem(const char* title, int value, int min, int max) : MenuEditableItem(title) {
    m_value = value;
    m_min = min;
    m_max = max;
}

int MenuEditableIntItem::getValue() {
    return m_value;
}

void MenuEditableIntItem::setValue(int value) {
    m_value = value;
    m_prevValue = value;
}

void MenuEditableIntItem::render(Adafruit_SSD1306* display, int x, int y, int w) {
    MenuEditableItem::render(display, x, y, w);
    display->setCursor(82, y);
    display->printf("%*d", 2, m_value);
    if (m_editing) {
        display->fillRect(80, y-1, 15, 10, SSD1306_INVERSE);
    }
}

bool MenuEditableIntItem::handleInput(int button) {
    if (MenuEditableItem::handleInput(button)) {
        switch (button) {
            case BUTTON_UP:
                m_value = (m_value >= m_max ? m_max : m_value+1);
                return true;
            case BUTTON_DOWN:
                m_value = (m_value <= m_min ? m_min : m_value-1);
                return true;
            case BUTTON_OK:
                m_prevValue = m_value;
                return true;
            case BUTTON_BACK:
                m_value = m_prevValue;
                return true;
        }
    }
    return false;
}