#include "MenuList.h"

MenuList::MenuList() {
    m_x = 0;
    m_y = 0;
    m_w = 0;
    m_h = 0;
    m_nLines = 0;
    m_nItems = 0;
    m_scrollbar = false;
    m_selected = -1;
    m_viewFirst = 0;
    m_onSelect = nullptr;
    m_onClick = nullptr;
}

int MenuList::addItem(MenuItem* item) {
    if (m_nItems >= ITEMS_MAX) {
        return -1;
    }
    m_items[m_nItems] = item;
    return m_nItems++;    
}

void MenuList::setLayout(int x, int y, int w, int nLines) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = nLines * ITEM_H;
    m_nLines = nLines;
}

void MenuList::setScrollbar(bool enabled) {
    m_scrollbar = enabled;
}

void MenuList::setSelected(int item) {
    if (m_selected >= 0 && m_selected < m_nItems) {
        m_items[m_selected]->setSelected(false);
    }
    if (item < 0 || item >= m_nItems) {
        m_selected = -1;
        adjustView();
    } else {
        m_selected = item;
        m_items[m_selected]->setSelected(true);
        adjustView();
    }
}

int MenuList::getSelected() {
    return m_selected;
}

MenuItem* MenuList::getItem(int item) {
    if (item >= 0 && item < m_nItems) {
        return m_items[item];
    }
    return nullptr;
}

void MenuList::onItemSelect(IMenuListItemSelectHandler* onSelect) {
    m_onSelect = onSelect;
}

void MenuList::onItemClick(IMenuListItemClickHandler* onClick) {
    m_onClick = onClick;
}

void MenuList::render(display_t* display) {
    int n = (m_nItems > m_nLines ? m_nLines : m_nItems);
    int i0 = m_viewFirst;
    int iN = i0 + n - 1;
    for (int i = i0; i <= iN; i++) {
        m_items[i]->render(display, m_x, m_y + (i - i0) * MenuList::ITEM_H, m_w - 3, MenuList::ITEM_H);
    }
    if (m_scrollbar) {
        float delta = 1.0 / m_nItems;
        int y0 = (((float)(m_h * m_selected)) * delta) + m_y;
        int y1 = (((float)(m_h * (m_selected + 1))) * delta) + m_y;
        display->drawFastVLine(m_x + m_w - 1, m_y, m_h, WHITE);
        display->drawFastVLine(m_x + m_w - 2, y0, y1-y0, WHITE);
    }
}

bool MenuList::handleInput(input_t* input) {
    if (m_selected != -1) {
        if (m_items[m_selected]->handleInput(input)) {
            return true;
        }
    }
    switch (input->button) {
        case BUTTON_UP:
            selectPrev();
            return true;
        case BUTTON_DOWN:
            selectNext();
            return true;
        case BUTTON_OK:
            if (m_onClick != nullptr) {
                (*m_onClick)(m_selected);
                return true;
            }
    }
    return false;
}

void MenuList::selectPrev() {
    if (m_nItems == 0) {
        m_selected = -1;
        if (m_onSelect != nullptr) {
            (*m_onSelect)(-1);
        }
        adjustView();
        return;
    }
    if (m_selected == -1) {
        m_selected = 0;
        m_items[m_selected]->setSelected(true);
        if (m_onSelect != nullptr) {
            (*m_onSelect)(m_selected);
        }
        adjustView();
        return;
    }
    m_items[m_selected]->setSelected(false);
    m_selected -= 1;
    if (m_selected < 0) {
        m_selected = m_nItems - 1;
    }
    m_items[m_selected]->setSelected(true);
    if (m_onSelect != nullptr) {
        (*m_onSelect)(m_selected);
    }
    adjustView();
}

void MenuList::selectNext() {
    if (m_nItems == 0) {
        m_selected = -1;
        if (m_onSelect != nullptr) {
            (*m_onSelect)(-1);
        }
        adjustView();
        return;
    }
    if (m_selected == -1) {
        m_selected = 0;
        m_items[m_selected]->setSelected(true);
        if (m_onSelect != nullptr) {
            (*m_onSelect)(m_selected);
        }
        adjustView();
        return;
    }
    m_items[m_selected]->setSelected(false);
    m_selected += 1;
    if (m_selected >= m_nItems) {
        m_selected = 0;
    }
    m_items[m_selected]->setSelected(true);
    if (m_onSelect != nullptr) {
        (*m_onSelect)(m_selected);
    }
    adjustView();
}

void MenuList::adjustView() {
    if (m_selected == -1 || m_nItems == 0) {
        m_viewFirst = 0;
        return;
    }
    if (m_selected >= m_viewFirst && m_selected < m_viewFirst + m_nLines) {
        return;
    }
    if (m_selected < m_viewFirst) {
        m_viewFirst = m_selected;
    }
    if (m_selected >= m_viewFirst + m_nLines) {
        m_viewFirst = m_selected - m_nLines + 1;
    }
    if (m_viewFirst < 0) {
        m_viewFirst = 0;
    }
}
