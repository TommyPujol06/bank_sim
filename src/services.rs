use crate::utils::{RandTable, Tcopy};
use std::fmt;

#[derive(Clone)]
pub struct Service {
    pub name: &'static str,
    pub wait_time: isize,
    pub cost: isize,
    pub demand: isize,
    pub profit: isize,
    pub offer: isize,
    pub usage: isize,
    pub backends: Option<Vec<Service>>,
}

impl Service {
    pub fn new(
        name: &'static str,
        wait_time: isize,
        cost: isize,
        demand: isize,
        profit: isize,
        offer: isize,
        usage: isize,
        backends: Option<Vec<Service>>,
    ) -> Self {
        Service {
            name,
            wait_time,
            cost,
            demand,
            profit,
            offer,
            usage,
            backends,
        }
    }

    pub fn set_config(&mut self, property: &str, value: isize) -> Result<(), &'static str> {
        match property {
            "name" => return Err("Can't change `name` value"),
            "wait_time" => self.wait_time = value,
            "cost" => self.cost = value,
            "demand" => self.demand = value,
            "profit" => self.profit = value,
            "offer" => self.offer = value,
            "usage" => self.usage = value,
            "backends" => return Err("Use `set_backend_config()` to configure backends"),
            _ => return Err("No such property name"),
        }

        Ok(())
    }

    pub fn add_backend(
        &mut self,
        name: &'static str,
        wait_time: isize,
        cost: isize,
        demand: isize,
        profit: isize,
        offer: isize,
        usage: isize,
        backends: Option<Vec<Service>>,
    ) {
        let backend = Service {
            name,
            wait_time,
            cost,
            demand,
            profit,
            offer,
            usage,
            backends,
        };

        self.backends
            .get_or_insert_with(|| Vec::new())
            .push(backend);
    }

    pub fn set_backend_config(
        backend: &mut Service,
        property: &str,
        value: isize,
    ) -> Result<(), &'static str> {
        Ok(backend.set_config(property, value)?)
    }
}

impl Tcopy for Service {
    fn copy(&mut self) -> Service {
        Service {
            name: self.name,
            wait_time: self.wait_time,
            cost: self.cost,
            demand: self.demand,
            profit: self.profit,
            offer: self.offer,
            usage: self.usage,
            backends: Some((*self.backends.get_or_insert_with(|| Vec::new()).clone()).to_vec()),
        }
    }
}

impl fmt::Display for Service {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.name)
    }
}

pub struct ServiceBucket {
    pub services: Vec<Service>,
    pub weights: Vec<u8>,
}

impl ServiceBucket {
    pub fn new() -> Self {
        Self {
            services: Vec::new(),
            weights: Vec::new(),
        }
    }

    pub fn push(&mut self, service: Service, weight: u8) {
        self.services.push(service);
        self.weights.push(weight);
    }

    pub fn find(&mut self, name: &'static str) -> Option<Service> {
        for service in &self.services {
            if service.name == name {
                return Some(service.clone());
            }
        }

        None
    }

    pub fn random(&mut self) -> Service {
        //
        // Need to see if it'd be worth only calculating the random table after each insert instead
        // of every time the random function is called.
        //
        RandTable::new(self.services.clone(), self.weights.clone()).random()
    }
}
