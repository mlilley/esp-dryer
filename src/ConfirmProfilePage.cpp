#include "ConfirmProfilePage.h"

#include "MenuEditableIntItem.h"

char* hoursTransformer(int value, int wchars) {
    double val = ((double)value)/10.0;
    char* str = (char*)malloc(sizeof(char)*(wchars+1));
    sprintf(str, "%4.1f", val);
    return str;
}

int hoursMutator(int value, bool up, bool longpress) {
    return value + (up ? 5 : -5) * (longpress ? 10 : 1);
}

ConfirmProfilePage::ConfirmProfilePage() {
    m_header = new MenuHeader("Confirm Profile:");

    MenuItem* items[5];
    items[0] = new MenuItem("START");
    items[1] = new MenuEditableIntItem("Temp", 0, TEMP_MIN, TEMP_MAX, 4, "%2d""\xF8""C", NULL, NULL);
    items[2] = new MenuEditableIntItem("Hours", 0, HOURS_MIN, HOURS_MAX, 4, NULL, &hoursTransformer, &hoursMutator);
    items[3] = new MenuItem("Save profile");
    items[4] = new MenuItem("Reset profile");
    m_list = new MenuList(0, 14, SCREEN_W, 5, items, 5, true);

    m_saveDialog = new MenuDialog(MenuDialog::KIND_OKCANCEL, "Save profile", "settings?");
    m_resetDialog = new MenuDialog(MenuDialog::KIND_OKCANCEL, "Reset profile", "to factory?");

    m_showSaveDialog = false;
    m_showResetDialog = false;
}

void ConfirmProfilePage::setProfile(profile_t* profile) {
    ((MenuEditableIntItem*)m_list->getItem(1))->setValue(profile->temp);
    ((MenuEditableIntItem*)m_list->getItem(2))->setValue(profile->hours);
}

void ConfirmProfilePage::activate(bool reset) {
    MenuPage::activate(reset);
    m_showSaveDialog = false;
    m_showResetDialog = false;
    if (reset) {
        m_list->selectItem(0);
    }
}

void ConfirmProfilePage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);
    m_header->render(display);
    m_list->render(display);
    if (m_showSaveDialog) {
        m_saveDialog->render(display);
    } else if (m_showResetDialog) {
        m_resetDialog->render(display);
    }
}

bool ConfirmProfilePage::handleInput(input_t input) {
    if (m_showSaveDialog) {
        m_saveDialog->handleInput(input);
        if (m_saveDialog->getState() == MenuDialog::STATE_OK) {
            // do save
            m_showSaveDialog = false;
        } else if (m_saveDialog->getState() == MenuDialog::STATE_CANCEL) {
            // do cancel
            m_showSaveDialog = false;
        }
        return true;
    } else if (m_showResetDialog) {
        m_resetDialog->handleInput(input);
        if (m_resetDialog->getState() == MenuDialog::STATE_OK) {
            // do reset
            m_showResetDialog = false;
        } else if (m_resetDialog->getState() == MenuDialog::STATE_CANCEL) {
            // do cancel
            m_showResetDialog = false;
        }
        return true;
    }
    if (m_list->handleInput(input)) {
        return true;
    }
    switch (input.button) {
        case BUTTON_OK:
            switch (m_list->getSelected()) {
                case 0: // start
                    m_accepted = true;
                    return true;
                case 3: // save
                    m_saveDialog->activate(1);
                    m_showSaveDialog = true;
                    return true;
                case 4: // reset
                    m_resetDialog->activate(1);
                    m_showResetDialog = true;
                    return true;
            }
            return false;
        case BUTTON_BACK:
            m_cancelled = true;
            return false;
    }
    return false;
}
