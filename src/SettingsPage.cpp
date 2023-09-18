#include "SettingsPage.h"

void onTempUnitChangeCallback(void* inst) {
    if (inst != NULL) {
        ((SettingsPage*)inst)->onTempUnitChange();
    }
}

void SettingsPage::refresh() {
    int newTempUnits = m_pConfig->getTempUnits();
    ((MenuEditableTempUnitsItem*)m_items[0])->setValue(newTempUnits);
}

SettingsPage::SettingsPage(ConfigStore* pConfig)
        : m_header(), m_list(), m_items{} {
    m_pConfig = pConfig;
    
    m_header.setTitle("Settings");

    m_items[0] = new MenuEditableTempUnitsItem("Units", m_pConfig->getTempUnits());
    m_items[1] = new MenuItem("Factory Reset");

    ((MenuEditableTempUnitsItem*)m_items[0])->setChangeHandler(&onTempUnitChangeCallback, this);

    m_list.setLayout(0, 14, SCREEN_W, 5);
    m_list.setScrollbarEnabled(true);
    m_list.setItems(m_items, 2);

    m_resetDialog.setKind(MenuDialog::KIND_OKCANCEL);
    m_resetDialog.setMsg("Reset all settings", "to factory?");
    
    m_showResetDialog = false;
}

void SettingsPage::activate(bool reset) {
    MenuPage::activate(reset);
    m_showResetDialog = false;
    if (reset) {
        m_list.setSelected(0);
    }
}

void SettingsPage::render(Adafruit_SSD1306* display) {
    MenuPage::render(display);
    m_header.render(display);
    m_list.render(display);
    if (m_showResetDialog) {
        m_resetDialog.render(display);
    }
}

bool SettingsPage::handleInput(input_t input) {
    if (m_showResetDialog) {
        m_resetDialog.handleInput(input);
        if (m_resetDialog.getState() == MenuDialog::STATE_OK) {
            // reset oked
            m_pConfig->reset();
            refresh();
            m_showResetDialog = false;
        } else if (m_resetDialog.getState() == MenuDialog::STATE_CANCEL) {
            m_showResetDialog = false;
        }
        return true;
    }
    if (m_list.handleInput(input)) {
        return true;
    }
    switch (input.button) {
        case BUTTON_OK:
            switch (m_list.getSelected()) {
                case 1: // reset
                    m_resetDialog.activate(1);
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

void SettingsPage::onTempUnitChange() {
    int newTempUnits = ((MenuEditableTempUnitsItem*)m_items[0])->getValue();
    m_pConfig->setTempUnits(newTempUnits);
    m_pConfig->persistTempUnits();
}