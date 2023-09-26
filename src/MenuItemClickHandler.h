#ifndef __MENU_ITEM_CLICK_HANDLER_H__
#define __MENU_ITEM_CLICK_HANDLER_H__

class IMenuItemClickHandler {
    public:
        virtual void operator() (void) = 0;
};

template<typename T>
class MenuItemClickHandler : public IMenuItemClickHandler {
    private:
        T* observer;
        void (T::*method)(void);

    public:    
        MenuItemClickHandler(T* observer, void (T::*method)(void)) 
                : observer(observer), method(method) { 
        }

        void operator() (void) override { 
            (observer->*method)();
        }
};

#endif