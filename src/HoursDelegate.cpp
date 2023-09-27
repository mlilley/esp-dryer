#include "HoursDelegate.h"

inline int myfloor(float v) {
    return v > 0 ? static_cast<int>(v) : static_cast<int>(v-1);
}

HoursDelegate::HoursDelegate(ConfigStore* config, int value) : MenuEditableItemDelegate() {
    m_config = config;
    m_value = value;
    m_originalValue = value;
}

void HoursDelegate::setValue(int value) {
    m_value = value;
    m_originalValue = value;
}

int HoursDelegate::getValue(void) {
    return m_value;
}

bool HoursDelegate::handleMsg(msg_t* msg) {
    if (IS_INPUT(msg)) {
        switch (msg->button) {
            case BUTTON_UP:
                m_value += (msg->longpress ? 3600 : 300);
                if (m_value > HOURS_MAX) {
                    m_value = HOURS_MAX;
                }
                return true;
            case BUTTON_DOWN:
                m_value -= (msg->longpress ? 3600 : 300);
                if (m_value < HOURS_MIN) {
                    m_value = HOURS_MIN;
                }
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

void HoursDelegate::render(display_t* display, int x, int y, int w, int h, bool isEditing) {
    static const int charsWide = 5;
    
    int xField = x + w - charsWide*6 - 3;
    int wField = charsWide*6 - 1;

    int hours = m_value / 3600;
    int mins = m_value % 3600 / 60;

    display->setCursor(xField, y);
    display->printf("%2d:%02d", hours, mins);
    if (isEditing) {
        display->fillRect(xField - 2, y - 1, wField + 4, 10, INVERSE);
    }
}

