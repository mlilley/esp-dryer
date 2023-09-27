#ifndef __ESP_DRYER__UNITS_DELEGATE_H__
#define __ESP_DRYER__UNITS_DELEGATE_H__

#include <Arduino.h>
#include "common.h"
#include "display.h"
#include "message.h"
#include "ConfigStore.h"
#include "MenuEditableItem.h"
#include "MenuEditableItemDelegate.h"

class UnitsDelegate : public MenuEditableItemDelegate {
    protected:
        ConfigStore* m_config;
        int m_value;
        int m_originalValue;
    
    public:
        UnitsDelegate(ConfigStore* config, int value);

        void setValue(int value);
        int getValue(void);

        bool handleMsg(msg_t* msg) override;
        void render(display_t* display, int x, int y, int w, int h, bool isEditing) override;
};

#endif