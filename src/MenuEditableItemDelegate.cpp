#include "MenuEditableItemDelegate.h"

MenuEditableItemDelegate::MenuEditableItemDelegate() {
    m_item = nullptr;
}

void MenuEditableItemDelegate::setItem(MenuEditableItem* item) {
    m_item = item;
}

void MenuEditableItemDelegate::commitValue(void) {
    if (m_item != nullptr) {
        m_item->commit();
    }
}

void MenuEditableItemDelegate::rejectValue(void) {
    if (m_item != nullptr) {
        m_item->reject();
    }
}
