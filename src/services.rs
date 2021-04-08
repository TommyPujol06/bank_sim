use strum::VariantNames;
use strum_macros::{EnumString, EnumVariantNames};

pub struct Service {
    pub wait_time: isize,
    pub cost: isize,
    pub demand: isize,
    pub profit: isize,
    pub offer: isize,
    pub usage: isize,
    pub backends: Vec<Service>,
}

impl Service {
    pub fn new(
        wait_time: isize,
        cost: isize,
        demand: isize,
        profit: isize,
        offer: isize,
        usage: isize,
        backends: Vec<Service>,
    ) -> Self {
        Service {
            wait_time,
            cost,
            demand,
            profit,
            offer,
            usage,
            backends,
        }
    }

    pub fn init() -> Vec<Service> {
        let mut tmp = Vec::<Service>::new();
        for _ in 0..7 {
            let s = Service::new(0, 0, 0, 0, 0, 0, Vec::<Service>::new());
            tmp.push(s);
        }

        tmp
    }

    pub fn set_config(&mut self, property: &str, value: isize) -> Result<(), &'static str> {
        match property {
            "wait_time" => self.wait_time = value,
            "cost" => self.cost = value,
            "demand" => self.demand = value,
            "profit" => self.profit = value,
            "offer" => self.offer = value,
            "usage" => self.usage = value,
            "backends" => return Err("use `set_backend_config()` to configure backends"),
            _ => return Err("No such property name"),
        }

        Ok(())
    }

    fn add_backend(
        &mut self,
        wait_time: isize,
        cost: isize,
        demand: isize,
        profit: isize,
        offer: isize,
        usage: isize,
        backends: Vec<Service>,
    ) {
        let backend = Service {
            wait_time,
            cost,
            demand,
            profit,
            offer,
            usage,
            backends,
        };

        self.backends.push(backend);
    }

    fn set_backend_config(
        backend: &mut Service,
        property: &str,
        value: isize,
    ) -> Result<(), &'static str> {
        Ok(backend.set_config(property, value)?)
    }
}

#[derive(Copy, Clone, EnumString, EnumVariantNames)]
#[strum(serialize_all = "UPPERCASE")]
pub enum Services {
    POS,
    ATM,
    WEB,
    APP,
    BOT,
    HHD,
    OFF,
}

impl Services {
    pub fn into_vec() -> Vec<&'static str> {
        let mut tmp = Vec::<&'static str>::new();
        for &item in Services::VARIANTS {
            tmp.push(item);
        }

        tmp
    }

    pub fn from_str(name: &str) -> Self {
        match name {
            "POS" => Services::POS,
            "ATM" => Services::ATM,
            "WEB" => Services::WEB,
            "APP" => Services::APP,
            "BOT" => Services::BOT,
            "HHD" => Services::HHD,
            _ => Services::OFF,
        }
    }

    pub fn to_str(&self) -> &str {
        match self {
            Services::POS => "POS",
            Services::ATM => "ATM",
            Services::WEB => "WEB",
            Services::APP => "APP",
            Services::BOT => "BOT",
            Services::HHD => "HHD",
            Services::OFF => "OFF",
        }
    }
}
