#include "random.h"
#include "services.h"
#include "clients.h"
#include "common.h"

void start() {
    int simulation_size;
    vector<Client> clients;
    ServiceBucket services;
    RandTable<int> priorities;

    std::cout << "Enter simulation size: ";
    std::cin >> simulation_size;
    std::cout << std::endl;

    std::cout << "Simulating " << simulation_size << " clients..." << std::endl;
    Core::populate_clients(simulation_size, clients, services, priorities);
}


int main() {
    std::cout << "Simulation started." << std::endl;
    start();
    std::cout << "Simulation ended." << std::endl;
    return 0;
}
