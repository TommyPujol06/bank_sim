use crate::services::{Service, ServiceBucket};
use crate::utils::RandTable;
use std::fmt;

pub struct Client<'a> {
    pub id: usize,
    pub priority: usize,
    pub elapsed_time: i128,
    pub service: Service<'a>,
}

pub fn populate_clients<'a>(
    num: usize,
    out: &mut Vec<Client<'a>>,
    service_bucket: ServiceBucket,
    priority_table: RandTable<usize>,
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

impl<'a> fmt::Display for Client<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "{};{};{};{}",
            self.id, self.service, self.priority, self.elapsed_time
        )
    }
}
