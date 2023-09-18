#include "MenuEditableTempUnitsItem.h"

MenuEditableTempUnitsItem::MenuEditableTempUnitsItem(const char* title, int value) 
        : MenuEditableItem(title) {
    m_value = value;
}

void MenuEditableTempUnitsItem::setTitle(const char* title) {
    m_title = title;
}

void MenuEditableTempUnitsItem::setValue(int value) {
    m_value = value;
    m_prevValue = value;
}

int MenuEditableTempUnitsItem::getValue() {
    return m_value;
}

void MenuEditableTempUnitsItem::render(Adafruit_SSD1306* display, int x, int y, int w) {
    MenuEditableItem::render(display, x, y, w);

    int fieldW = 6 * 2;
    int fieldX = x + w - 1 -2 - fieldW; // right aligned

    display->setCursor(fieldX, y);
    display->print(m_value == UNITS_C ? "\xF8""C" : "\xF8""F");
    if (m_editing) {
        display->fillRect(fieldX - 2, y - 1, fieldW + 4 - 1, 10, SSD1306_INVERSE);
    }
}

bool MenuEditableTempUnitsItem::handleInput(input_t input) {
    if (MenuEditableItem::handleInput(input)) {
        switch (input.button) {
            case BUTTON_UP:
            case BUTTON_DOWN:
                if (m_value == UNITS_C) {
                    m_value = UNITS_F;
                } else {
                    m_value = UNITS_C;
                }
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