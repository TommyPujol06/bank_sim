//
// Created by Tommy Pujol on 4/19/21.
//

#ifndef BANK_SIM_CLIENTS_H
#define BANK_SIM_CLIENTS_H

#include "elapsed_time.h"
#include "services.h"

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

#endif //BANK_SIM_CLIENTS_H
