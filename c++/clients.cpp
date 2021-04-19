//
// Created by Tommy Pujol on 4/19/21.
//

#include "clients.h"
#include "random.h"

#include <boost/format.hpp>

string Client::to_string() {
    return boost::str(boost::format("%d;%s;%d;%d") % this->id % this->service.name % this->priority % this->elapsed_time);
}

void populate_clients
(int num, vector<Client>& out, ServiceBucket& service_bucket, RandTable<int>& priority_table)
{
    for (int i=0; i != num; i++) {
        out.push_back(Client {
            i, priority_table.random(), 0, service_bucket.random()
        });
    }
}