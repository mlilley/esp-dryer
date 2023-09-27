#ifndef __ESP_DRYER__MENU_PAGE_COMPLETION_HANDLER_H__
#define __ESP_DRYER__MENU_PAGE_COMPLETION_HANDLER_H__

class IMenuPageCompletionHandler {
    public:
        virtual void operator() (int result) = 0;
};

template<typename T>
class MenuPageCompletionHandler : public IMenuPageCompletionHandler {
    private:
        T* observer;
        void (T::*method)(int result);

    public:    
        MenuPageCompletionHandler(T* observer, void (T::*method)(int)) 
                : observer(observer), method(method) { 
        }

        void operator() (int result) override { 
            (observer->*method)(result);
        }
};

#endif