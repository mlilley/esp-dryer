#include "MenuActionItem.h"

#include "common.h"
#include "MenuItem.h"
#include <Adafruit_SSD1306.h>

MenuActionItem::MenuActionItem() : MenuItem("") {
}

void MenuActionItem::render(Adafruit_SSD1306* display, int y) {
    MenuItem::render(display, 0, 0, 0);
}

bool MenuActionItem::onButton(int button) {
    switch (button) {
        case BUTTON_UP:
            return false;
        case BUTTON_DOWN:
            return false;
        case BUTTON_OK:
            return true;
        case BUTTON_BACK:
            return false;
    }
    return false;
}