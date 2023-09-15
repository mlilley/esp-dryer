#include "ConfirmProfilePage.h"

#include "MenuEditableIntItem.h"

ConfirmProfilePage::ConfirmProfilePage() {
    m_header = new MenuHeader("Confirm Profile:");

    MenuItem* items[6];
    items[0] = new MenuItem("START");
    items[1] = new MenuEditableIntItem("Temp", 0, TEMP_MIN, TEMP_MAX, 2);
    items[2] = new MenuEditableIntItem("Hours", 0, HOURS_MIN, HOURS_MAX, 2);
    items[3] = new MenuItem("Save");
    items[4] = new MenuItem("Reset");
    m_list = new MenuList(28, 14, 72, 5, items, 6, true); // 11ch + 1 => 72px => (128-72)/2 => 28px

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
        Serial.print("CPP:input->save\n");
        m_saveDialog->handleInput(input);
        if (m_saveDialog->getState() == MenuDialog::STATE_OK) {
            // do save
            Serial.print("DO-SAVE!\n");
            m_showSaveDialog = false;
        } else if (m_saveDialog->getState() == MenuDialog::STATE_CANCEL) {
            // do cancel
            Serial.print("SAVE-CANCELLED!\n");
            m_showSaveDialog = false;
        }
        return true;
    } else if (m_showResetDialog) {
        Serial.print("CPP:input->reset\n");
        m_resetDialog->handleInput(input);
        if (m_resetDialog->getState() == MenuDialog::STATE_OK) {
            // do reset
            Serial.print("DO-RESET!\n");
            m_showResetDialog = false;
        } else if (m_resetDialog->getState() == MenuDialog::STATE_CANCEL) {
            // do cancel
            Serial.print("RESET-CANCELLED!\n");
            m_showResetDialog = false;
        }
        return true;
    }
    if (m_list->handleInput(input)) {
        Serial.print("CPP:input->list\n");
        return true;
    }
    Serial.print("CPP:input->(self)\n");
    switch (input.button) {
        case BUTTON_OK:
            switch (m_list->getSelected()) {
                case 0: // start
                    m_accepted = true;
                    return true;
                case 4: // save
                    m_saveDialog->activate(1);
                    m_showSaveDialog = true;
                    return true;
                case 5: // reset
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