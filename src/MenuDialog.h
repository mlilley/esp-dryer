#ifndef __ESP_DRYER__MENU_DIALOG_H__
#define __ESP_DRYER__MENU_DIALOG_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
#include "MenuDialogCloseHandler.h"

class MenuDialog {
    protected:
        static const int W = SCREEN_W - 12;
        static const int H = SCREEN_H - 12;
        static const int X = (SCREEN_W - W) / 2;
        static const int Y = (SCREEN_H - H) / 2;

        int m_kind;
        const char* m_line1;
        const char* m_line2;
        int m_selected;
        IMenuDialogCloseHandler* m_onClose;
        
    public:
        static const int KIND_OK = 0;
        static const int KIND_OKCANCEL = 1;
        static const int RESULT_OK = 0;
        static const int RESULT_CANCEL = 1;

        MenuDialog(int kind);

        void activate(int selected);
        void setMsg(const char* line1, const char* line2);
        void setSelected(int button);
        void onClose(IMenuDialogCloseHandler* onClose);
      
        void render(display_t* display);
        bool handleMsg(msg_t* msg);
};

#endif