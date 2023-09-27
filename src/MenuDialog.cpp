#include "MenuDialog.h"

MenuDialog::MenuDialog(int kind) {
    m_kind = kind;
    m_line1 = nullptr;
    m_line2 = nullptr;
    m_onClose = nullptr;
}

void MenuDialog::activate(int selected) {
    MenuDialog::setSelected(selected);
}

void MenuDialog::setMsg(const char* line1, const char* line2) {
    m_line1 = line1;
    m_line2 = line2;
}

void MenuDialog::setSelected(int button) {
    m_selected = button;
}

void MenuDialog::onClose(IMenuDialogCloseHandler* onClose) {
    m_onClose = onClose;
}

void MenuDialog::render(display_t* display) {
    display->fillRect(X, Y, W, H, BLACK);
    display->drawRect(X+1, Y+1, W-2, H-2, WHITE);
    
    display->setTextColor(WHITE);
    display->setTextSize(1);
    display->setCursor(X + 12, Y + 8);
    display->print(m_line1 == NULL ? "" : m_line1);
    display->setCursor(X + 12, Y + 18);
    display->print(m_line2 == NULL ? "" : m_line2);
    
    if (m_kind == KIND_OK) {
        display->setCursor(48, Y + 38);
        display->print("OK");
        if (m_selected == 0) {
            display->fillRect(46, Y + 37, 15, 10, INVERSE);
        }
    } else if (m_kind == KIND_OKCANCEL) {
        display->setCursor(X + 12, Y + 38);
        display->print("OK");
        display->setCursor(X + W - 1 - 12 - 36, Y + 38);
        display->print("CANCEL");
        if (m_selected == 0) {
            display->fillRect(X + 12 - 2, Y + 38 - 1, 2 * 6 + 4 - 1, 10, INVERSE);
        } else if (m_selected == 1) {
            display->fillRect(X + W - 1 - 12 - 36 - 2, Y + 38 - 1, 36 + 4 - 1, 10, INVERSE);
        }        
    }
}

bool MenuDialog::handleMsg(msg_t* msg) {
    if (IS_INPUT(msg)) {
        switch (msg->button) {
            case BUTTON_UP:
            case BUTTON_DOWN:
                m_selected = (m_kind == KIND_OK ? 0 : m_selected == 0 ? 1 : 0);
                return true;
            case BUTTON_OK:
                if (m_onClose != nullptr) {
                    (*m_onClose)(m_kind == KIND_OKCANCEL && m_selected == 1 ? RESULT_CANCEL : RESULT_OK);
                }
                return true;
            case BUTTON_BACK:
                if (m_onClose != nullptr) {
                    (*m_onClose)(RESULT_CANCEL);
                }
                return true;
        }
    }
    return false;
}
