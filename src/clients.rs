use crate::services::Services;
use crate::utils::RandTable;
use std::fmt;
use strum::VariantNames;
use strum_macros::{EnumString, EnumVariantNames};

#[derive(Copy, Clone, EnumString, EnumVariantNames)]
#[strum(serialize_all = "camel_case")]
pub enum Priorities {
    Low,
    Medium,
    High,
}

impl Priorities {
    pub fn into_vec() -> Vec<&'static str> {
        let mut tmp = Vec::<&'static str>::new();
        for &item in Priorities::VARIANTS {
            tmp.push(item);
        }

        tmp
    }

    pub fn from_str(name: &str) -> Self {
        match name {
            "Low" => Priorities::Low,
            "Medium" => Priorities::Medium,
            _ => Priorities::High,
        }
    }

    pub fn to_str(&self) -> &str {
        match self {
            Priorities::Low => "Low",
            Priorities::Medium => "Medium",
            Priorities::High => "High",
        }
    }
}

pub struct Client {
    pub id: usize,
    pub priority: Priorities,
    pub elapsed_time: i128,
    pub service: Services,
}

pub fn populate_clients(
    num: usize,
    priority_table: RandTable<&str>,
    services_table: RandTable<&str>,
) -> Vec<Client> {
    let mut clients = Vec::<Client>::new();

    for id in 0..num {
        let priority_str = priority_table.random();
        let service_str = services_table.random();

        clients.push(Client {
            id: id,
            priority: Priorities::from_str(priority_str),
            elapsed_time: 0,
            service: Services::from_str(service_str),
        });
    }

    clients
}

impl fmt::Display for Client {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "{};{};{};{}",
            self.id,
            self.service.to_str(),
            self.priority.to_str(),
            self.elapsed_time
        )
    }
}
