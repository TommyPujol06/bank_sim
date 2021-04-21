//
// Created by Tommy Pujol on 4/19/21.
//

#include "clients.h"

std::string Client::to_string() {
    return boost::str(boost::format("%d;%s;%d;%d") % this->id % this->service->name % this->priority % Time::human_time(this->elapsed_time));
}

namespace Core {
    void populate_clients(int num, vector<Client> &out, ServiceBucket service_bucket, RandTable<int> &priority_table) {
        for (int i = 0; i != num; i++) {
            out.emplace_back(Client(
                    i, *priority_table.random(), Time::none(), service_bucket.random()
            ));
        }
    }
}