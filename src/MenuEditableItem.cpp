#include "MenuEditableItem.h"

MenuEditableItem::MenuEditableItem(const char* title, MenuEditableItemDelegate* delegate) : MenuItem(title) {
    m_editing = false;
    m_delegate = delegate;
    m_delegate->setItem(this);
    m_onChange = nullptr;
}

bool MenuEditableItem::isEditing(void) {
    return m_editing;
}

void MenuEditableItem::onChange(IMenuEditableItemChangeHandler* onChange) {
    m_onChange = onChange;
}

void MenuEditableItem::commit(void) {
    m_editing = false;
    if (m_onChange != nullptr) {
        (*m_onChange)();
    }
}

void MenuEditableItem::reject(void) {
    m_editing = false;
}

MenuEditableItemDelegate* MenuEditableItem::getDelegate(void) {
    return m_delegate;
}

void MenuEditableItem::render(display_t* display, int x, int y, int w, int h) {
    MenuItem::render(display, x, y, w, h);
    m_delegate->render(display, x, y, w, h, m_editing);
}

bool MenuEditableItem::handleInput(input_t* input) {
    if (m_editing) {
        return m_delegate->handleInput(input);
    }
    if (input->button == BUTTON_OK) {
        m_editing = true;
        return true;
    }
    return false;
}