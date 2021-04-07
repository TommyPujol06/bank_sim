use strum::VariantNames;
use strum_macros::{EnumString, EnumVariantNames};

pub struct Service {
    pub wait_time: u64,
    pub cost: f64,
    pub demand: u64,
    pub profit: i64,
    pub offer: u64,
    pub usage: u64,
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
