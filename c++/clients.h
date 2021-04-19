//
// Created by Tommy Pujol on 4/19/21.
//

#ifndef BANK_SIM_CLIENTS_H
#define BANK_SIM_CLIENTS_H

#include "services.h"

using std::string;
using std::vector;

class Client {
public:
   int id;
   int priority;
   // FIXME: need to use a better time keeping data structure.
   int elapsed_time;
   Service service;

   string to_string();
};


#endif //BANK_SIM_CLIENTS_H
