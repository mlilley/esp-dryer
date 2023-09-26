#include "MenuItem.h"

MenuItem::MenuItem() : MenuItem("") {
}

MenuItem::MenuItem(const char* title) {
    m_title = title;
    m_selected = false;
    m_onClick = nullptr;
}

void MenuItem::setTitle(const char* title) {
    m_title = title;
}

void MenuItem::setSelected(bool selected) {
    m_selected = selected;
}

void MenuItem::onClick(IMenuItemClickHandler* onClick) {
    m_onClick = onClick;
}

void MenuItem::render(display_t* display, int x, int y, int w, int h) {
    display->setTextColor(WHITE);
    if (m_selected) {
        display->setCursor(x, y);
        display->print("\x10");
    }
    display->setCursor(x+8, y);
    display->printf("%s",(m_title == NULL ? "" : m_title));
}

bool MenuItem::handleInput(input_t* input) {
    switch (input->button) {
        case BUTTON_OK:
            if (m_onClick != nullptr) {
                (*m_onClick)();
                return true;
            }
    }
    return false;
}