extern crate pretty_env_logger;
#[derive(Debug, Clone)]
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
