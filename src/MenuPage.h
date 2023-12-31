#ifndef __ESP_DRYER__MENU_PAGE_H__
#define __ESP_DRYER__MENU_PAGE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
#include "MenuPageCompletionHandler.h"

#define MENU_PAGE_RESULT_OK 1
#define MENU_PAGE_RESULT_BACK 0

class MenuPage {
    protected:
        IMenuPageCompletionHandler* m_onComplete;

    public:
        MenuPage();
        virtual void onComplete(IMenuPageCompletionHandler* onComplete);
        virtual void activate(bool reset);
        virtual void render(display_t* display);
        virtual bool handleMsg(msg_t* msg);
};

#endif