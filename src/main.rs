mod clients;
mod services;
mod utils;

use crate::clients::{populate_clients, Priorities};
use crate::services::Services;
use crate::utils::RandTable;

const CLIENT_NUMER: usize = 10_000_000;

fn main() {
    let pweights = vec![70, 20, 10];
    let sweights = vec![10, 10, 30, 30, 10, 5, 5];

    let priorities = &Priorities::into_vec();
    let services = &Services::into_vec();

    let ptable = RandTable::new(priorities, pweights);
    let stable = RandTable::new(services, sweights);

    let clients = populate_clients(CLIENT_NUMER, ptable, stable);

    for client in clients {
        println!("{}", client);
    }
}
