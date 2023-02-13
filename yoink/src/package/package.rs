extern crate pretty_env_logger;
use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Package {
    pub name: String,
    pub base: String,
    pub ver: String,
    pub timestamp: String,
}

impl Package {
    pub fn new(name: String, base: String, ver: String, timestamp: String) -> Package {
        Package {
            name,
            base,
            ver,
            timestamp,
        }
    }

    pub fn default() -> Package {
        Package::new(
            String::from(""),
            String::from(""),
            String::from(""),
            String::from(""),
        )
    }

    pub fn log(self) {
        info!(
            "{} {} {} {}",
            self.name, self.base, self.ver, self.timestamp
        );
    }

    pub fn get_package_name(self) -> String {
        let name = format!("{}-{}.tar", self.base, self.ver);
        String::from(name)
    }
}
