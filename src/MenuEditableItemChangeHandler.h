#ifndef __MENU_EDITABLE_ITEM_CHANGE_HANDLER_H__
#define __MENU_EDITABLE_ITEM_CHANGE_HANDLER_H__

class IMenuEditableItemChangeHandler {
    public:
        virtual void operator() (void) = 0;
};

template<typename T>
class MenuEditableItemChangeHandler : public IMenuEditableItemChangeHandler {
    private:
        T* observer;
        void (T::*method)(void);

    public:    
        MenuEditableItemChangeHandler(T* observer, void (T::*method)(void)) 
                : observer(observer), method(method) { 
        }

        void operator() (void) override { 
            (observer->*method)();
        }
};

#endif