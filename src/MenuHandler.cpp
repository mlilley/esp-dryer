#include "MenuHandler.h"

#include "common.h"
#include "HomePage.h"
#include "SelectProfilePage.h"
#include "ConfirmProfilePage.h"
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306* _display;
static xQueueHandle _queueInput;
static profile_t* _profiles;

static HomePage* _homePage;
static SelectProfilePage* _selectProfilePage;
static ConfirmProfilePage* _confirmProfilePage;

void setupMenuHandler(Adafruit_SSD1306* display, profile_t profiles[], int nProfiles, xQueueHandle queueInput) {
    _display = display;
    _queueInput = queueInput;
    _profiles = profiles;

    _homePage = new HomePage();
    _selectProfilePage = new SelectProfilePage(profiles, nProfiles);
    _confirmProfilePage = new ConfirmProfilePage();
}

MenuPage* handleInput(input_t input, MenuPage* menuPage) {
    menuPage->handleInput(input);
    if (menuPage->isAccepted()) {
        if (menuPage == _homePage) {
            if (*((int*)(_homePage->getAcceptedValue())) == 0) {
                _selectProfilePage->activate(true);
                return _selectProfilePage;
            }
            // TODO
            _homePage->activate(false);
            return menuPage;
        }
        if (menuPage == _selectProfilePage) {
            profile_t profile = _profiles[*((int*)(_selectProfilePage->getAcceptedValue()))];
            _confirmProfilePage->setProfile(&profile);
            _confirmProfilePage->activate(true);
            return _confirmProfilePage;
        }
        if (menuPage == _confirmProfilePage) {
            // TODO
            _confirmProfilePage->activate(true);
            return _confirmProfilePage;
        }
        return menuPage;
    }
    if (menuPage->isCancelled()) {
        if (menuPage == _selectProfilePage) {
            _homePage->activate(false);
            return _homePage;
        }
        if (menuPage == _confirmProfilePage) {
            _selectProfilePage->activate(false);
            return _selectProfilePage;
        }
    }
    return menuPage;
}

void taskMenuHandler(void* params) {
    input_t input;
    MenuPage* menuPage = _homePage;

    menuPage->activate(true);
    menuPage->render(_display);
    _display->display();

    for (;;) {
        if (xQueueReceive(_queueInput, &input, 500)) {
            menuPage = handleInput(input, menuPage);
            menuPage->render(_display);
            _display->display();
        }
    }
}