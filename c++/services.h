//
// Created by Tommy Pujol on 4/19/21.
//

#ifndef BANK_SIM_SERVICES_H
#define BANK_SIM_SERVICES_H

#include "random.h"
#include "common.h"

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

    int set_config(const char* property, long new_value);
    void add_backend(const Service& backend);
};

class ServiceBucket {
public:
    vector<Service> services;
    vector<int> weights;
    RandTable<Service> services_table;

    void push(Service& service, int weight);
    void remove(const char* name) const;

    [[maybe_unused]] std::optional<Service> find(const char* name);
    Service* random();

    ServiceBucket() {
        this->renew_random_table();
    }

private:
    void renew_random_table();
};

#endif //BANK_SIM_SERVICES_H
