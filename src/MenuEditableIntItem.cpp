#include "MenuEditableIntItem.h"

MenuEditableIntItem::MenuEditableIntItem(const char* title, int value, int min, int max, int wchars, const char* fmt, intTransformer_t transformer, intMutator_t mutator) : MenuEditableItem(title) {
    m_value = value;
    m_min = min;
    m_max = max;
    m_wchars = wchars;
    m_fmt = fmt;
    m_transformer = transformer;
    m_mutator = mutator;
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

    int fieldW = 6 * m_wchars;
    int fieldX = x + w - 1 - 2 - fieldW; // aligned to list right edge

    display->setCursor(fieldX, y);
    if (m_transformer == NULL) {
        display->printf(m_fmt, m_value);
    } else {
        char* strval = (*m_transformer)(m_value, m_wchars);
        display->print(strval);
    }
    if (m_editing) {
        display->fillRect(fieldX - 2, y - 1, fieldW + 4 - 1, 10, SSD1306_INVERSE);
    }
}

bool MenuEditableIntItem::handleInput(input_t input) {
    if (MenuEditableItem::handleInput(input)) {
        switch (input.button) {
            case BUTTON_UP:
                if (m_mutator != NULL) {
                    m_value = (*m_mutator)(m_value, true, input.longpress);
                } else {
                    m_value += (input.longpress ? 5 : 1);
                }
                if (m_value >= m_max) m_value = m_max;
                return true;
            case BUTTON_DOWN:
                if (m_mutator != NULL) {
                    m_value = (*m_mutator)(m_value, false, input.longpress);
                } else {
                    m_value -= (input.longpress ? 5 : 1);
                }
                if (m_value <= m_min) m_value = m_min;
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