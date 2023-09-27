#include "TempDelegate.h"

inline int myfloor(float v) {
    return v > 0 ? static_cast<int>(v) : static_cast<int>(v-1);
}

TempDelegate::TempDelegate(ConfigStore* config, int value) : MenuEditableItemDelegate() {
    m_config = config;
    m_value = value;
    m_originalValue = value;
}

void TempDelegate::setValue(int value) {
    m_value = value;
    m_originalValue = value;
}

int TempDelegate::getValue(void) {
    return m_value;
}

bool TempDelegate::handleMsg(msg_t* msg) {
    if (IS_INPUT(msg)) {
        switch (msg->button) {
            case BUTTON_UP:
                m_value += (msg->longpress ? 10 : 5);
                if (m_value > TEMP_MAX) {
                    m_value = TEMP_MAX;
                }
                return true;
            case BUTTON_DOWN:
                m_value -= (msg->longpress ? 10 : 5);
                if (m_value < TEMP_MIN) {
                    m_value = TEMP_MIN;
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

void TempDelegate::render(display_t* display, int x, int y, int w, int h, bool isEditing) {
    static const int charsWide = 5;

    int xField = x + w - charsWide*6 - 3;
    int wField = charsWide*6 - 1;

    display->setCursor(xField, y);
    if (m_config->getTempUnits() == UNITS_C) {
        display->printf("%3d\xF8""C", m_value);
    } else {
        display->printf("%3d\xF8""F", myfloor(static_cast<float>(m_value) * 9.0f / 5.0f + 32.0f));
    }
    if (isEditing) {
        display->fillRect(xField - 2, y - 1, wField + 4, 10, INVERSE);
    }
}

