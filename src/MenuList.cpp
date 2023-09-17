#include "MenuList.h"

MenuList::MenuList() {
}

MenuList::MenuList(int x, int y, int w, int nLines, MenuItem* items[], int nItems, bool scrollbarEnabled) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = nLines * MenuItem::H;
    m_nLines = nLines;
    for (int i = 0; i < nItems; i++) {
        m_items[i] = items[i];
    }
    m_nItems = nItems;
    m_selected = -1;
    m_viewFirst = 0;
    m_scrollbarEnabled = scrollbarEnabled;
}

void MenuList::setLayout(int x, int y, int w, int nLines) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = nLines * MenuItem::H;
    m_nLines = nLines;
}

void MenuList::setScrollbarEnabled(bool enabled) {
    m_scrollbarEnabled = enabled;
}

void MenuList::setItems(MenuItem* items[], int nItems) {
    int n = (nItems > ITEMS_MAX ? ITEMS_MAX : nItems);
    for (int i = 0; i < n; i++) {
        m_items[i] = items[i];
    }
    m_nItems = n;
    m_selected = -1;
    adjustView();
}

void MenuList::setSelected(int item) {
    if (m_selected >= 0 && m_selected < m_nItems) {
        m_items[m_selected]->setSelected(false);
    }

    int prevSelected = m_selected;
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
    return NULL;
}

void MenuList::render(Adafruit_SSD1306* display) {
    int n = (m_nItems > m_nLines ? m_nLines : m_nItems);
    int i0 = m_viewFirst;
    int iN = i0 + n - 1;
    int nItem = 0;
    for (int i = i0; i <= iN; i++) {
        MenuItem* menuItem = m_items[nItem];
        m_items[i]->render(display, m_x, m_y + nItem * MenuItem::H, m_w - 3);
        nItem++;
    }

    if (m_scrollbarEnabled) {
        float delta = 1.0 / m_nItems;
        int y0 = (((float)(m_h * m_selected)) * delta) + m_y;
        int y1 = (((float)(m_h * (m_selected + 1))) * delta) + m_y;
        display->drawFastVLine(m_x + m_w - 1, m_y, m_h, SSD1306_WHITE);
        display->drawFastVLine(m_x + m_w - 2, y0, y1-y0, SSD1306_WHITE);
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
    if (m_nItems == 0) {
        m_selected = -1;
        adjustView();
        return;
    }
    if (m_selected == -1) {
        m_selected = 0;
        m_items[m_selected]->setSelected(true);
        adjustView();
        return;
    }
    m_items[m_selected]->setSelected(false);
    m_selected -= 1;
    if (m_selected < 0) {
        m_selected = m_nItems - 1;
    }
    m_items[m_selected]->setSelected(true);
    adjustView();
}

void MenuList::selectNext() {
    if (m_nItems == 0) {
        m_selected = -1;
        adjustView();
        return;
    }
    if (m_selected == -1) {
        m_selected = 0;
        m_items[m_selected]->setSelected(true);
        adjustView();
        return;
    }
    m_items[m_selected]->setSelected(false);
    m_selected += 1;
    if (m_selected >= m_nItems) {
        m_selected = 0;
    }
    m_items[m_selected]->setSelected(true);
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
