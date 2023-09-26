#ifndef __MENU_EDITABLE_ITEM_H__
#define __MENU_EDITABLE_ITEM_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "MenuItem.h"
#include "MenuEditableItemDelegate.h"
#include "MenuEditableItemChangeHandler.h"

class MenuEditableItemDelegate;

class MenuEditableItem : public MenuItem {
    friend class MenuEditableItemDelegate;

    protected:
        bool m_editing;
        MenuEditableItemDelegate* m_delegate;
        IMenuEditableItemChangeHandler* m_onChange;

        void commit(void);
        void reject(void);

    public:
        MenuEditableItem(const char* title, MenuEditableItemDelegate* delegate);
        bool isEditing(void);
        void onChange(IMenuEditableItemChangeHandler* onChange);
        MenuEditableItemDelegate* getDelegate();

        virtual void render(display_t* display, int x, int y, int w, int h);
        virtual bool handleInput(input_t* input);
};

#endif