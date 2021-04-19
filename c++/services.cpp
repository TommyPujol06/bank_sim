//
// Created by tommy on 4/19/21.
//

#include "services.h"
#include <boost/range/adaptor/indexed.hpp>

void ServiceBucket::push(Service service, int weight) {
    this->services.push_back(service);
    this->weights.push_back(weight);
    this->renew_random_table();
}

void ServiceBucket::find() {

}

Service ServiceBucket::random() {
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

/*
int Service::set_config(const char *property, long new_value) {

    if (property == "name") return -1;

        case "wait_time": this->wait_time = new_value;
        case "cost": this->cost = new_value;

        default: return -1;
    }
    return -1;
}
*/

void Service::add_backend(Service backend) {

}
