#ifndef __MENU_DIALOG_H__
#define __MENU_DIALOG_H__

#include "common.h"
#include <Adafruit_SSD1306.h>

class MenuDialog {
    public:
        static const int KIND_OK = 0;
        static const int KIND_OKCANCEL = 1;
        static const int STATE_OPEN = 0;
        static const int STATE_OK = 1;
        static const int STATE_CANCEL = 2;

    protected:
        static const int W = SCREEN_W - 12;
        static const int H = SCREEN_H - 12;
        static const int X = (SCREEN_W - W) / 2;
        static const int Y = (SCREEN_H - H) / 2;

    protected:
        int m_kind;
        const char* m_line1;
        const char* m_line2;
        int m_state;
        int m_selected;
        
    public:
        MenuDialog();
        MenuDialog(int kind, const char* line1, const char* line2);
        void activate(int selected);
        void setKind(int kind);
        void setMsg(const char* line1, const char* line2);
        void setSelected(int button);
        int getState();
        void render(Adafruit_SSD1306* display);
        bool handleInput(input_t input);
};

#endif