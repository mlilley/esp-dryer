#ifndef __MENU_EDITABLE_ITEM_DELEGATE_H__
#define __MENU_EDITABLE_ITEM_DELEGATE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "MenuEditableItem.h"

class MenuEditableItem;

class MenuEditableItemDelegate {
    friend class MenuEditableItem;

    protected:
        MenuEditableItem* m_item;

        void commitValue(void);
        void rejectValue(void);
        void setItem(MenuEditableItem* item);

    public:
        MenuEditableItemDelegate();
        virtual bool handleInput(input_t* input) = 0;
        virtual void render(display_t* display, int x, int y, int w, int h, bool isEditing) = 0;
};

#endif