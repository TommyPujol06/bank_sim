//
// Created by Tommy Pujol on 4/19/21.
//

#ifndef BANK_SIM_RANDOM_H
#define BANK_SIM_RANDOM_H

#include "common.h"

template <typename T>
class RandTable {
public:
    int len{};
    vector<T> data;

    RandTable() {
        this->len = 0;
    }

    RandTable(vector<T> data, vector<int> weights);
    T* random();
};

template<typename T>
RandTable<T>::RandTable(vector<T> data, vector<int> weights) {
    assert(data.size() == weights.size());

    for (auto tup : boost::combine(data, weights)) {
        T obj;
        int weight;
        boost::tie(obj, weight) = tup;

        for (int i=0; i != weight; i++) {
            this->data.push_back(obj);
        }
    }

    this->len = this->data.size();
}

template<typename T>
T* RandTable<T>::random() {

    if(this->len == 0) {
        throw std::runtime_error("Can't choose a random item from an empty list.");
    }

    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> number(1, this->len);
    int rand = number(rng);
    return &this->data[rand - 1];
}


#endif //BANK_SIM_RANDOM_H
