#include "MenuEditableItem.h"

MenuEditableItem::MenuEditableItem(const char* title) : MenuItem(title) {
    m_editing = false;
    m_onChange = NULL;
    m_onChangeMethodInstance = NULL;
}

void MenuEditableItem::setChangeHandler(onChange_t handler, void* instance) {
    m_onChange = handler;
    m_onChangeMethodInstance = instance;
}

void MenuEditableItem::render(Adafruit_SSD1306* display, int x, int y, int w) {
    MenuItem::render(display, x, y, w);
}

bool MenuEditableItem::handleInput(input_t input) {
    if (m_editing) {
        switch (input.button) {
            case BUTTON_UP:
                return true;
            case BUTTON_DOWN:
                return true;
            case BUTTON_OK:
                m_editing = false;
                if (m_onChange != NULL) {
                    (*m_onChange)(m_onChangeMethodInstance);
                }
                return true;
            case BUTTON_BACK:
                m_editing = false;
                return true;
        }
    } else {
        switch (input.button) {
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