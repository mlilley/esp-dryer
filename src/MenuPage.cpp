#include "MenuPage.h"

#include "common.h"
#include <Adafruit_SSD1306.h>

MenuPage::MenuPage() {
    m_accepted = false;
    m_cancelled = false;
    m_acceptedValue = NULL;
}

bool MenuPage::isAccepted() {
    return m_accepted;
}

bool MenuPage::isCancelled() {
    return m_cancelled;
}

void MenuPage::activate(bool reset) {
    m_accepted = false;
    m_cancelled = false;
    m_acceptedValue = NULL;
}

void* MenuPage::getAcceptedValue() {
    return m_acceptedValue;
}

void MenuPage::render(Adafruit_SSD1306* display) {
    display->clearDisplay();
}

bool MenuPage::handleInput(int button) {
    return false;
}