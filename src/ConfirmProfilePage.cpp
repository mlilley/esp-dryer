#include "ConfirmProfilePage.h"

ConfirmProfilePage::ConfirmProfilePage(ConfigStore* config) : MenuPage(), m_config(config) {
    m_header = new MenuHeader("Confirm Profile");

    m_items[0] = new MenuItem("START");
    m_items[1] = new MenuEditableItem("Temp", new TempDelegate(config, 0));
    m_items[2] = new MenuEditableItem("Time", new HoursDelegate(config, 0));
    m_items[3] = new MenuItem("Save Profile");
    m_items[4] = new MenuItem("Reset Profile");

    m_items[0]->onClick(new MenuItemClickHandler<ConfirmProfilePage>(this, &ConfirmProfilePage::onStartClick));
    m_items[3]->onClick(new MenuItemClickHandler<ConfirmProfilePage>(this, &ConfirmProfilePage::onSaveClick));
    m_items[4]->onClick(new MenuItemClickHandler<ConfirmProfilePage>(this, &ConfirmProfilePage::onResetClick));

    m_list = new MenuList();
    m_list->setLayout(0, 14, SCREEN_W, 5);
    m_list->setScrollbar(true);

    m_list->addItem(m_items[0]);
    m_list->addItem(m_items[1]);
    m_list->addItem(m_items[2]);
    m_list->addItem(m_items[3]);
    m_list->addItem(m_items[4]);

    m_saveDialog = new MenuDialog(MenuDialog::KIND_OKCANCEL);
    m_saveDialog->setMsg("Save profile", "settings?");
    m_saveDialog->onClose(new MenuDialogCloseHandler<ConfirmProfilePage>(this, &ConfirmProfilePage::onSaveDialogClose));
        
    m_resetDialog = new MenuDialog(MenuDialog::KIND_OKCANCEL);
    m_resetDialog->setMsg("Reset profile", "to factory?");
    m_resetDialog->onClose(new MenuDialogCloseHandler<ConfirmProfilePage>(this, &ConfirmProfilePage::onResetDialogClose));

    m_showSaveDialog = false;
    m_showResetDialog = false;
}

void ConfirmProfilePage::activate(bool reset) {
    MenuPage::activate(reset);
    m_showSaveDialog = false;
    m_showResetDialog = false;
    if (reset) {
        m_list->setSelected(0);
    }
}

void ConfirmProfilePage::setProfile(int index) {
    m_profile = index;
    const profile_t* profile = m_config->getProfile(index);
    ((TempDelegate*)((MenuEditableItem*)m_items[1])->getDelegate())->setValue(profile->temp);
    ((HoursDelegate*)((MenuEditableItem*)m_items[2])->getDelegate())->setValue(profile->hours);
}

profile_t ConfirmProfilePage::getConfirmedProfile(void) {
    profile_t profile = {
        .temp = ((TempDelegate*)((MenuEditableItem*)m_items[1])->getDelegate())->getValue(),
        .hours = ((HoursDelegate*)((MenuEditableItem*)m_items[2])->getDelegate())->getValue(),
        .state = m_config->getProfile(m_profile)->state
    };
    strcpy(profile.name, m_config->getProfile(m_profile)->name);
    return profile;
}

void ConfirmProfilePage::render(display_t* display) {
    MenuPage::render(display);
    m_header->render(display);
    m_list->render(display);
    if (m_showSaveDialog) {
        m_saveDialog->render(display);
    } else if (m_showResetDialog) {
        m_resetDialog->render(display);
    }
}

bool ConfirmProfilePage::handleInput(input_t* input) {
    if (m_showSaveDialog) {
        return m_saveDialog->handleInput(input);
    } else if (m_showResetDialog) {
        return m_resetDialog->handleInput(input);
    }
    if (m_list->handleInput(input)) {
        return true;
    }
    return MenuPage::handleInput(input);
}

void ConfirmProfilePage::onStartClick(void) {
    if (m_onComplete != nullptr) {
        (*m_onComplete)(MENU_PAGE_RESULT_OK);
    }
}

void ConfirmProfilePage::onSaveClick(void) {
    m_showSaveDialog = true;
    m_saveDialog->activate(1);
}

void ConfirmProfilePage::onResetClick(void) {
    m_showResetDialog = true;
    m_saveDialog->activate(1);
}

void ConfirmProfilePage::onSaveDialogClose(int result) {
    if (result == MenuDialog::RESULT_OK) {
        profile_t profile = {
            .temp = ((TempDelegate*)((MenuEditableItem*)m_items[1])->getDelegate())->getValue(),
            .hours = ((HoursDelegate*)((MenuEditableItem*)m_items[2])->getDelegate())->getValue(),
            .state = m_config->getProfile(m_profile)->state
        };
        strcpy(profile.name, m_config->getProfile(m_profile)->name);
        m_config->setProfile(m_profile, &profile);
        m_config->persistProfile(m_profile);
    }
    m_showSaveDialog = false;
}

void ConfirmProfilePage::onResetDialogClose(int result) {
    if (result == MenuDialog::RESULT_OK) {
        m_config->resetProfile(m_profile);
        setProfile(m_profile);
    }
    m_showResetDialog = false;
}