#ifndef __MENU_LIST_ITEM_SELECT_HANDLER_H__
#define __MENU_LIST_ITEM_SELECT_HANDLER_H__

class IMenuListItemSelectHandler {
    public:
        virtual void operator() (int index) = 0;
};

template<typename T>
class MenuListItemSelectHandler : public IMenuListItemSelectHandler {
    private:
        T* observer;
        void (T::*method)(int index);

    public:
        MenuListItemSelectHandler(T* observer, void (T::*method)(int))
                : observer(observer), method(method) {
        }

        void operator() (int index) override {
            (observer->*method)(index);
        }
};

#endif