//
// Created by Tommy Pujol on 4/19/21.
//

#ifndef BANK_SIM_SERVICES_H
#define BANK_SIM_SERVICES_H

#include "random.h"
#include <algorithm>

class Service {
public:
    const char* name;
    long wait_time;
    long cost;
    long demand;
    long profit;
    long offer;
    long usage;
    vector<Service> backends;

    // FIXME: Need to have a better return type to include errors.
    // Maybe use something similar to Rust's: Result<(), &'static str>
    int set_config(const char* property, long new_value);
    void add_backend(Service backend);
};

class ServiceBucket {
public:
    vector<Service> services;
    vector<int> weights;
    RandTable<Service> services_table;

    void push(Service service, int weight);
    void remove(const char* name) const;
    void find();
    Service random();

private:
    void renew_random_table();
};

#endif //BANK_SIM_SERVICES_H
