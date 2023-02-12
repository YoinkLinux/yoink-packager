extern crate pretty_env_logger;
use serde::{Deserialize, Serialize};
use serde_json::{Result, Value};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Package {
    name: String,
    base: String,
    ver: String,
}

impl Package {
    pub fn new(name: String, base: String, ver: String) -> Package {
        Package { name, base, ver }
    }

    pub fn log(self) {
        info!("{} {} {}", self.name, self.base, self.ver);
    }

    pub fn get_package_name(self) -> String {
        let name = format!("{}-{}.tar", self.base, self.ver);
        String::from(name)
    }
}
