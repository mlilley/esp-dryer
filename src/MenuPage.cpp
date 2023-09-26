#include "MenuPage.h"

#include "common.h"
#include "display.h"

MenuPage::MenuPage() {
    m_onComplete = nullptr;
}

void MenuPage::onComplete(IMenuPageCompletionHandler* onComplete) {
    m_onComplete = onComplete;
}

void MenuPage::activate(bool reset) {
}

void MenuPage::render(display_t* display) {
    display->clearDisplay();
}

bool MenuPage::handleInput(input_t* input) {
    if (input->button == BUTTON_OK) {
        if (m_onComplete != nullptr) {
            (*m_onComplete)(MENU_PAGE_RESULT_OK);
            return true;
        }
    }
    if (input->button == BUTTON_BACK) {
        if (m_onComplete != nullptr) {
            (*m_onComplete)(MENU_PAGE_RESULT_BACK);
            return true;
        }
    }
    return false;
}