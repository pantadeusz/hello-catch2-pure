#ifndef __DATABASE_C_HPP___
#define __DATABASE_C_HPP___
#include <list>
#include <map>

template <class T>
class database_c {
    public:
    std::map<std::string,T> data_;

    std::list<T> get_all(){
        std::list<T> ret;
        for (auto &[k,v]:data_) ret.push_back(v);
        return ret;
    };

    void put(std::string id, const T value) {
        data_[id] = value;
    }

    void remove(std::string id) {
        if (data_.count(id)) {
            data_.erase(id);
        } else {
            throw std::invalid_argument("element does not exist");
        }
    }
};

#endif