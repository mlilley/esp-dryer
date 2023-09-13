#include "HomePage.h"

#include "MenuPage.h"
#include <Adafruit_SSD1306.h>

HomePage::HomePage() : MenuPage() {
}

void HomePage::activate(bool reset) {
    MenuPage::activate(reset);
    if (reset) { }
}

void HomePage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);
    display->setTextColor(SSD1306_WHITE);
    display->setTextSize(2);
    display->setCursor(0,0);
    display->print("EspDryer");
    display->setTextSize(1);
    display->setCursor(104,7);
    display->printf("v%s", VERSION);
    display->drawFastHLine(0, 17, SCREEN_W, SSD1306_WHITE);

    display->setTextSize(2);
    display->setCursor(38, 28);
    display->printf("%*d\xF8""C", 2, 45);

    display->setTextSize(1);
    display->setCursor(2, 56);
    display->print(">  READY TO START  <");
    display->fillRect(0, 55, SCREEN_W, 9, SSD1306_INVERSE);
}

bool HomePage::handleInput(int button) {
    if (button == BUTTON_OK) {
        m_accepted = true;
        return true;
    }
    return false;
}
