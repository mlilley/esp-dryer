#ifndef __MENU_LIST_ITEM_CLICK_HANDLER_H__
#define __MENU_LIST_ITEM_CLICK_HANDLER_H__

class IMenuListItemClickHandler {
    public:
        virtual void operator() (int index) = 0;
};

template<typename T>
class MenuListItemClickHandler : public IMenuListItemClickHandler {
    private:
        T* observer;
        void (T::*method)(int index);

    public:    
        MenuListItemClickHandler(T* observer, void (T::*method)(int)) 
                : observer(observer), method(method) { 
        }

        void operator() (int index) override { 
            (observer->*method)(index);
        }
};

#endif