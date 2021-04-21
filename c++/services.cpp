//
// Created by Tommy Pujol on 4/19/21.
//

#include "services.h"

void ServiceBucket::push(Service& service, int weight) {
    this->services.push_back(service);
    this->weights.push_back(weight);
    this->renew_random_table();
}

[[maybe_unused]]
std::optional<Service> ServiceBucket::find(const char* name) {
    // FIXME: Use a more efficient search algorithm.
    for (auto& service : this->services) {
        if(strcmp(service.name, name) == 0) return service;
    }

    return {};
}

Service* ServiceBucket::random() {
    return this->services_table.random();
}

[[maybe_unused]]
void ServiceBucket::remove(const char *name) const {
    vector<Service> vec = this->services;
    int idx = 0;
    for (auto& service : vec) {
        if (service.name == name) {
            break;
        }

        idx++;
    }

    vec.erase(vec.begin() + idx);
}

void ServiceBucket::renew_random_table() {
    this->services_table = RandTable<Service>(this->services, this->weights);
}

[[maybe_unused]]
int Service::set_config(const char *property, long new_value) {

    if (strcmp(property, "wait_time") == 0) { this->wait_time = new_value; return 0; }
    else if (strcmp(property, "cost") == 0) { this->cost = new_value; return 0; }
    else if (strcmp(property, "demand") == 0) { this->demand = new_value; return 0; }
    else if (strcmp(property, "profit") == 0) { this->profit = new_value; return 0; }
    else if (strcmp(property, "offer") == 0) { this->offer = new_value; return 0; }
    else if (strcmp(property, "usage") == 0) { this->usage = new_value; return 0; }
    else { return -1; }
}

[[maybe_unused]]
void Service::add_backend(const Service& backend) {
    this->backends.push_back(backend);
}