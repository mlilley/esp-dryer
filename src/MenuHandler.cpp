#include "MenuHandler.h"

#include "common.h"
#include "HomePage.h"
#include "SelectProfilePage.h"
#include "ConfirmProfilePage.h"

static ConfigStore* _config;
static xQueueHandle _queueInput;
static Adafruit_SSD1306* _display;

static HomePage* _homePage;
static SelectProfilePage* _selectProfilePage;
static ConfirmProfilePage* _confirmProfilePage;

void setupMenuHandler(ConfigStore* config, xQueueHandle queueInput, Adafruit_SSD1306* display) {
    _config = config;
    _queueInput = queueInput;
    _display = display;

    _homePage = new HomePage();
    _selectProfilePage = new SelectProfilePage(_config);
    _confirmProfilePage = new ConfirmProfilePage(_config);
}

typedef struct transition_t {
    MenuPage* toPage;
    bool reset;
} transition_t;

transition_t afterInput_HomePage() {
    if (_homePage->isAccepted()) {
        if (*((int*)(_homePage->getAcceptedValue())) == 0) {
            // Start selected
            return (transition_t){ _selectProfilePage, true };
        } else if (*((int*)(_homePage->getAcceptedValue())) == 1) {
            // Settings selected (TODO)
            // return (transition_t){ _settingsPage, true };
            _homePage->activate(false);
        }
    }
    return (transition_t){};
}

transition_t afterInput_SelectProfilePage() {
    if (_selectProfilePage->isAccepted()) {
        _confirmProfilePage->setProfile(*(int*)(_selectProfilePage->getAcceptedValue()));
        return (transition_t){ _confirmProfilePage, true };
    } else if (_selectProfilePage->isCancelled()) {
        return (transition_t){ _homePage, false };
    }
    return (transition_t){};
}

transition_t afterInput_ConfirmProfilePage() {
    if (_confirmProfilePage->isAccepted()) {
        // Profile confirmed (TODO)
        // return (transition_t){ _runPage, true };
        _confirmProfilePage->activate(false);
    } else if (_confirmProfilePage->isCancelled()) {
        return (transition_t){ _selectProfilePage, false };
    }
    return (transition_t){};
}

MenuPage* handleInput(input_t input, MenuPage* currentPage) {
    transition_t transition;

    currentPage->handleInput(input);

    if (currentPage == _homePage) {
        transition = afterInput_HomePage();
    } else if (currentPage == _selectProfilePage) {
        transition = afterInput_SelectProfilePage();
    } else if (currentPage == _confirmProfilePage) {
        transition = afterInput_ConfirmProfilePage();
    }

    if (transition.toPage != NULL) {
        transition.toPage->activate(transition.reset);
        currentPage = transition.toPage;
    }

    return currentPage;
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