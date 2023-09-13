#include "MenuEditableItem.h"

MenuEditableItem::MenuEditableItem(const char* title) : MenuItem(title) {
    m_editing = false;
}

void MenuEditableItem::render(Adafruit_SSD1306* display, int x, int y, int w) {
    MenuItem::render(display, x, y, w);
}

bool MenuEditableItem::handleInput(int button) {
    if (m_editing) {
        switch (button) {
            case BUTTON_UP:
                return true;
            case BUTTON_DOWN:
                return true;
            case BUTTON_OK:
                m_editing = false;
                return true;
            case BUTTON_BACK:
                m_editing = false;
                return true;
        }
    } else {
        switch (button) {
            case BUTTON_UP:
                return false;
            case BUTTON_DOWN:
                return false;
            case BUTTON_OK:
                m_editing = true;
                return true;
            case BUTTON_BACK:
                return false;
        }
    }
    return false;
}