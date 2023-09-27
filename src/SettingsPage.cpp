#include "SettingsPage.h"

SettingsPage::SettingsPage(ConfigStore* config) : MenuPage(), m_config(config) {
    m_header = new MenuHeader("Settings");

    m_items[0] = new MenuEditableItem("Units", new UnitsDelegate(config, config->getTempUnits()));
    ((MenuEditableItem*)m_items[0])->onChange(new MenuEditableItemChangeHandler<SettingsPage>(this, &SettingsPage::onUnitsChange));

    m_items[1] = new MenuItem("Factory Reset");
    m_items[1]->onClick(new MenuItemClickHandler<SettingsPage>(this, &SettingsPage::onResetClick));

    m_list = new MenuList();
    m_list->setLayout(0, 14, SCREEN_W, 5);
    m_list->setScrollbar(true);
    m_list->addItem(m_items[0]);
    m_list->addItem(m_items[1]);

    m_resetDialog = new MenuDialog(MenuDialog::KIND_OKCANCEL);
    m_resetDialog->setMsg("Reset to factory", "defaults?");
    m_resetDialog->onClose(new MenuDialogCloseHandler<SettingsPage>(this, &SettingsPage::onResetClose));

    m_showResetDialog = false;   
}

void SettingsPage::activate(bool reset) {
    MenuPage::activate(reset);
    m_showResetDialog = false;
    if (reset) {
        m_list->setSelected(0);
    }
}

void SettingsPage::render(display_t* display) {
    MenuPage::render(display);
    m_header->render(display);
    m_list->render(display);
    if (m_showResetDialog) {
        m_resetDialog->render(display);
    }
}

bool SettingsPage::handleMsg(msg_t* msg) {
    if (m_showResetDialog) {
        return m_resetDialog->handleMsg(msg);
    }
    if (m_list->handleMsg(msg)) {
        return true;
    }
    return MenuPage::handleMsg(msg);
}

void SettingsPage::refresh() {
    ((UnitsDelegate*)((MenuEditableItem*)m_items[0])->getDelegate())->setValue(m_config->getTempUnits());
}

void SettingsPage::onResetClick(void) {
    m_resetDialog->activate(1);
    m_showResetDialog = true;
}

void SettingsPage::onResetClose(int result) {
    if (result == MenuDialog::RESULT_OK) {
        m_config->reset();
        refresh();
    }    
    m_showResetDialog = false;
}

void SettingsPage::onUnitsChange(void) {
    m_config->setTempUnits(((UnitsDelegate*)((MenuEditableItem*)m_items[0])->getDelegate())->getValue());
    m_config->persistTempUnits();
}
