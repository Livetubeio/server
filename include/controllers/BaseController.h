//
// Created by stevijo on 28.09.16.
//

#ifndef LIVEPLAYLIST_BASECONTROLLER_H
#define LIVEPLAYLIST_BASECONTROLLER_H

template<typename T>
class BaseController {
public:
    static T* instance() {
        static Guard g;
        if(!_instance) {
            _instance = new T;
        }
        return _instance;
    }
private:
    static T* _instance;
    class Guard {
    public: ~Guard() {
            if(nullptr != _instance) {
                delete _instance;
                _instance = nullptr;
            }
        }
    };
};
template<typename T>
T* BaseController<T>::_instance = nullptr;

#endif
