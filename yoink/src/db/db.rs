use crate::package::package::Package;

use parse_duration::parse;
use std::time::Duration;
pub struct Database {
    pub packages: Vec<Package>,
}

impl Database {

    pub fn new() -> Database {
        Database {
            packages: vec![]
        }
    }

    pub fn ensure_created() -> sqlite::Connection {
        let conn = sqlite::open("/tmp/yoink.sql").unwrap();

        let query = "CREATE TABLE IF NOT EXISTS Packages
        (name TEXT, base TEXT, ver TEXT, timestamp  TEXT);";
        debug!("Creating table if not exists...");
        let status = conn.execute(query).unwrap();
        debug!("{:?}", status);
        conn
    }

    pub fn get_connection(self) -> sqlite::Connection {
        Database::ensure_created()
    }

    pub fn get_packages(self) -> Vec<Package> {
        let query = "SELECT * FROM Packages";
        let conn = self.get_connection();
        let mut packages = Vec::new();
        for row in conn
            .prepare(query)
            .unwrap()
            .into_iter()
            .map(|row| row.unwrap())
        {
            let name = String::from(row.read::<&str, _>("name"));
            let base = String::from(row.read::<&str, _>("base"));
            let ver = String::from(row.read::<&str, _>("ver"));
            let ts = String::from(row.read::<&str, _>("timestamp"));
            let timestamp = parse(&ts).unwrap();
            let package = Package {
                name,
                base,
                ver,
                timestamp,
            };
            packages.push(package)
        }
        packages
    }

    pub fn insert_package(self, package: &Package) {
        let query = "INSERT INTO Packages VALUES(?,?,?,?)";
        let conn = Database::get_connection(self);
        let mut statement = conn.prepare(query).unwrap();
        statement.bind((1, package.name.as_str())).unwrap();
        statement.bind((2, package.base.as_str())).unwrap();
        statement.bind((3, package.ver.as_str())).unwrap();
        statement.bind((4, package.timestamp.as_secs().to_string().as_str())).unwrap();
        statement.next();
    }
}
