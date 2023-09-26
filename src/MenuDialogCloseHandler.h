#ifndef __MENU_DIALOG_CLOSE_HANDLER_H__
#define __MENU_DIALOG_CLOSE_HANDLER_H__

class IMenuDialogCloseHandler {
    public:
        virtual void operator() (int result) = 0;
};

template<typename T>
class MenuDialogCloseHandler : public IMenuDialogCloseHandler {
    private:
        T* observer;
        void (T::*method)(int result);

    public:    
        MenuDialogCloseHandler(T* observer, void (T::*method)(int)) 
                : observer(observer), method(method) { 
        }

        void operator() (int result) override { 
            (observer->*method)(result);
        }
};

#endif