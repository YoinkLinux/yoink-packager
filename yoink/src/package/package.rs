extern crate pretty_env_logger;
use std::time::{Duration, SystemTime};

use serde::{Deserialize, Serialize};
use serde_json::{Result, Value};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Package {
    pub name: String,
    pub base: String,
    pub ver: String,
    pub timestamp: Duration,
}

impl Package {
    pub fn new(name: String, base: String, ver: String) -> Package {
        let timestamp = SystemTime::now()
            .duration_since(SystemTime::UNIX_EPOCH)
            .unwrap();
        Package {
            name,
            base,
            ver,
            timestamp,
        }
    }

    pub fn log(self) {
        info!(
            "{} {} {} {}",
            self.name,
            self.base,
            self.ver,
            self.timestamp.as_secs()
        );
    }

    pub fn get_package_name(self) -> String {
        let name = format!("{}-{}.tar", self.base, self.ver);
        String::from(name)
    }
}
