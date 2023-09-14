#include "MenuList.h"

MenuList::MenuList(int x, int y, int w, int lines, MenuItem* items[], int nItems) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = lines * MenuItem::H;
    m_lines = lines;
    for (int i = 0; i < nItems; i++) {
        m_items[i] = items[i];
    }
    m_nItems = nItems;
    m_selected = -1;
    m_viewFirst = 0;
}

void MenuList::selectItem(int item) {
    if (m_selected == item) {
        return;
    }
    if (m_selected != -1) {
        m_items[m_selected]->setSelected(false);
    }
    if (item < 0 || item >= m_nItems) {
        m_selected = -1;
        return;
    }
    m_selected = item;
    m_items[m_selected]->setSelected(true);
    adjustView(ADJUSTVIEW_MODE_TOPOF);
}

int MenuList::getSelected() {
    return m_selected;
}

MenuItem* MenuList::getItem(int item) {
    if (item >= 0 && item < m_nItems) {
        return m_items[item];
    }
    return NULL;
}

void MenuList::render(Adafruit_SSD1306* display) {
    int n = (m_nItems > m_lines ? m_lines : m_nItems);
    int i0 = m_viewFirst;
    int iN = i0 + n - 1;
    int nItem = 0;
    for (int i = i0; i <= iN; i++) {
        MenuItem* menuItem = m_items[nItem];
        m_items[i]->render(display, m_x, m_y + nItem * MenuItem::H, m_w);
        nItem++;
    }
}

bool MenuList::handleInput(input_t input) {
    // If something is selected, ask it to handle the button
    if (m_selected != -1 && m_items[m_selected]->handleInput(input)) {
        return true;
    }
    // If nothing selected, or selected didn't handle it, we'll handle it
    switch (input.button) {
        case BUTTON_UP:
            selectPrev();
            return true;
        case BUTTON_DOWN:
            selectNext();
            return true;
    }
    return false;
}

void MenuList::selectPrev() {
    if (m_nItems == 0) return;
    if (m_selected == -1) {
        m_selected = 0;
        m_items[m_selected]->setSelected(true);
        adjustView(ADJUSTVIEW_MODE_TOPOF);
        return;
    }
    m_items[m_selected]->setSelected(false);
    m_selected = (m_selected <= 0 ? m_nItems - 1 : m_selected - 1);
    m_items[m_selected]->setSelected(true);
    adjustView(ADJUSTVIEW_MODE_TOPOF);
}

void MenuList::selectNext() {
    if (m_nItems == 0) return;
    if (m_selected == -1) {
        m_selected = 0;
        m_items[m_selected]->setSelected(true);
        adjustView(ADJUSTVIEW_MODE_TOPOF);
        return;
    }
    m_items[m_selected]->setSelected(false);
    m_selected = (m_selected >= m_nItems - 1 ? 0 : m_selected + 1);
    m_items[m_selected]->setSelected(true);
    adjustView(ADJUSTVIEW_MODE_BOTTOMOF);
}

void MenuList::adjustView(int mode) {
    // If nothing selected, then TOPOF puts view top at list top, and BOTTOMOF
    // puts view bottom at list bottom.
    if (m_selected == -1) {
        if (mode == ADJUSTVIEW_MODE_TOPOF) {
            m_viewFirst = 0;
        } else {
            m_viewFirst = m_nItems - m_lines;
            if (m_viewFirst < 0) {
                m_viewFirst = 0;
            }
        }
    // With something selected, TOPOF puts selected at view top, BOTTOMOF puts
    // selected at view bottom, if selected is not already within view.
    } else {
        // Do nothing if selected is alreay in view.
        if (m_selected >= m_viewFirst && m_selected <= m_viewFirst + m_lines - 1) {
            return;
        }
        // Shift the selected item into view according to the mode.
        if (mode == ADJUSTVIEW_MODE_TOPOF) {
            m_viewFirst = m_selected;
        } else {
            m_viewFirst = m_selected - m_lines + 1;
        }
        // Shift view box back within list bounds.
        if (m_viewFirst + m_nItems - 1 > m_nItems) {
            m_viewFirst = m_nItems - m_lines;
        }
        if (m_viewFirst <= 0) {
            m_viewFirst = 0;
        }
    }
}