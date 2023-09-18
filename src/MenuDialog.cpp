#include "MenuDialog.h"

MenuDialog::MenuDialog() {
    m_kind = 0;
    m_line1 = NULL;
    m_line2 = NULL;
    m_state = 0;
}

MenuDialog::MenuDialog(int kind, const char* line1, const char* line2) {
    m_kind = kind;
    m_line1 = line1;
    m_line2 = line2;
    m_state = 0;
}

void MenuDialog::activate(int selected) {
    m_state = 0;
    MenuDialog::setSelected(selected);
}

void MenuDialog::setKind(int kind) {
    if (kind == 0 || kind == 1 || kind == 2) {
        m_kind = kind;
    }
}

void MenuDialog::setMsg(const char* line1, const char* line2) {
    m_line1 = line1;
    m_line2 = line2;
}

void MenuDialog::setSelected(int button) {
    m_selected = button;
}

int MenuDialog::getState() {
    return m_state;
}

void MenuDialog::render(Adafruit_SSD1306* display) {
    display->fillRect(X, Y, W, H, SSD1306_BLACK);
    display->drawRect(X+1, Y+1, W-2, H-2, SSD1306_WHITE);
    
    display->setTextColor(SSD1306_WHITE);
    display->setTextSize(1);
    display->setCursor(X + 12, Y + 8);
    display->print(m_line1 == NULL ? "" : m_line1);
    display->setCursor(X + 12, Y + 18);
    display->print(m_line2 == NULL ? "" : m_line2);
    
    if (m_kind == KIND_OK) {
        display->setCursor(48, Y + 38);
        display->print("OK");
        if (m_selected == 0) {
            display->fillRect(46, Y + 37, 15, 10, SSD1306_INVERSE);
        }
    } else if (m_kind == KIND_OKCANCEL) {
        display->setCursor(X + 12, Y + 38);
        display->print("OK");
        display->setCursor(X + W - 1 - 12 - 36, Y + 38);
        display->print("CANCEL");
        if (m_selected == 0) {
            display->fillRect(X + 12 - 2, Y + 38 - 1, 2 * 6 + 4 - 1, 10, SSD1306_INVERSE);
        } else if (m_selected == 1) {
            display->fillRect(X + W - 1 - 12 - 36 - 2, Y + 38 - 1, 36 + 4 - 1, 10, SSD1306_INVERSE);
        }        
    }
}

bool MenuDialog::handleInput(input_t input) {
    
    switch (input.button) {
        case BUTTON_UP:
        case BUTTON_DOWN:
            if (m_kind == KIND_OK) {
                m_selected = 0;
            } else if (m_kind == KIND_OKCANCEL) {
                m_selected = (m_selected == 0 ? 1 : 0);
            }
            break;
        case BUTTON_OK:
            if (m_kind == KIND_OK) {
                m_state = 1;
            } else if (m_kind == KIND_OKCANCEL) {
                m_state = (m_selected == 1 ? 2 : 1);
            }
            break;
        case BUTTON_BACK:
            if (m_kind == KIND_OK) {
                m_state = 1;
            } else if (m_kind == KIND_OKCANCEL) {
                m_state = 2;
            }
            break;
    }
    return true;
}
