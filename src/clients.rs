use crate::services::{Service, ServiceBucket};
use crate::utils::RandTable;
use std::fmt;

pub struct Client {
    pub id: usize,
    pub priority: usize,
    pub elapsed_time: i128,
    pub service: Service,
}

pub fn populate_clients(
    num: usize,
    out: &mut Vec<Client>,
    service_bucket: &mut ServiceBucket,
    priority_table: &mut RandTable<usize>,
) {
    for id in 0..num {
        out.push(Client {
            id: id,
            priority: priority_table.random(),
            elapsed_time: 0,
            service: service_bucket.random(),
        });
    }
}

impl fmt::Display for Client {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "{};{};{};{}",
            self.id, self.service, self.priority, self.elapsed_time
        )
    }
}
