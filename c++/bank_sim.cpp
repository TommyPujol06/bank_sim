//
// Created by Tommy Pujol on 4/24/21.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <optional>
#include <stdexcept>

#include <boost/format.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/combine.hpp>
#include <boost/random.hpp>

using std::vector;

struct TimeElapsed {
    int years;
    int months;
    int days;
    int hours;
    int minutes;
    int seconds;
    int microseconds;
};

namespace Time {
    TimeElapsed none() {
        return TimeElapsed{
                0, 0, 0, 0, 0, 0, 0
        };
    }

    std::string human_time(TimeElapsed& t) {
        return boost::str(boost::format("%d/%d/%d-%d:%d:%d%d%d") % t.years % t.months % t.days % t.hours %
                          t.minutes % t.seconds % t.microseconds);
    }
}

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
    // FIXME: make a better random table.
    assert(data.size() == weights.size());

    for (const auto& tup : boost::combine(data, weights)) {
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

class Service {
public:
    const char* name;
    long wait_time;
    long cost;
    long demand;
    long profit;
    long offer;
    long usage;
    vector<Service>* backends;

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
    this->backends->push_back(backend);
}

class Client {
public:
    int id;
    int priority;

    TimeElapsed elapsed_time{};
    Service* service;

    std::string to_string();

    Client(int id, int priority, TimeElapsed elapsed_time, Service* service) {
        this->id = id;
        this->priority = priority;
        this->service = service;
    }
};

namespace Core {
    void populate_clients(int num, vector<Client> &out, ServiceBucket service_bucket, RandTable<int> &priority_table);
}


std::string Client::to_string() {
    return boost::str(boost::format("%d;%s;%d;%d") % this->id % this->service->name % this->priority % Time::human_time(this->elapsed_time));
}

// FIXME: Pass services & random table as pointers to avoid unnecessary copies.
void populate_clients(int num, vector<Client> &out, ServiceBucket service_bucket, RandTable<int> &priority_table) {
    for (int i = 0; i != num; i++) {
        out.emplace_back(Client(
                i, *priority_table.random(), Time::none(), service_bucket.random()
        ));
    }
}


int main() {
    int simulation_size;
    vector<Client> clients;
    ServiceBucket services;
    RandTable<int> priorities;

    std::cout << "Simulation started." << std::endl;

    std::cout << "Enter simulation size: ";
    std::cin >> simulation_size;
    std::cout << std::endl;

    // TODO: Make interface to init services.
    std::cout << "Simulating " << simulation_size << " clients..." << std::endl;
    populate_clients(simulation_size, clients, services, priorities);

    std::cout << "Simulation ended." << std::endl;
}
