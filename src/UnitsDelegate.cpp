#include "UnitsDelegate.h"

inline int myfloor(float v) {
    return v > 0 ? static_cast<int>(v) : static_cast<int>(v-1);
}

UnitsDelegate::UnitsDelegate(ConfigStore* config, int value) : MenuEditableItemDelegate() {
    m_config = config;
    m_value = value;
    m_originalValue = value;
}

void UnitsDelegate::setValue(int value) {
    m_value = value;
    m_originalValue = value;
}

int UnitsDelegate::getValue(void) {
    return m_value;
}

bool UnitsDelegate::handleMsg(msg_t* msg) {
    if (IS_INPUT(msg)) {
        switch (msg->button) {
            case BUTTON_UP:
            case BUTTON_DOWN:
                m_value = (m_value == UNITS_C ? UNITS_F : UNITS_C);
                return true;
            case BUTTON_OK:
                m_originalValue = m_value;
                commitValue();
                return true;
            case BUTTON_BACK:
                m_value = m_originalValue;
                rejectValue();
                return true;
        }
    }
    return false;
}

void UnitsDelegate::render(display_t* display, int x, int y, int w, int h, bool isEditing) {
    static const int charsWide = 2;

    int xField = x + w - charsWide*6 - 3;
    int wField = charsWide*6 - 1;
    
    display->setCursor(xField, y);
    if (m_value == UNITS_C) {
        display->print("\xF8""C");
    } else {
        display->printf("\xF8""F");
    }
    if (isEditing) {
        display->fillRect(xField - 2, y - 1, wField + 4, 10, INVERSE);
    }
}

