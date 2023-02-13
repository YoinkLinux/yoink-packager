use crate::package::package::Package;

use sqlite::State;
pub struct Database {
    pub packages: Vec<Package>,
}

impl Database {
    pub fn new() -> Database {
        Database { packages: vec![] }
    }

    pub fn ensure_created() -> sqlite::Connection {
        let conn = sqlite::open("/tmp/yoink.sql").unwrap();

        let query = "CREATE TABLE IF NOT EXISTS Packages
        (name TEXT PRIMARY KEY, base TEXT, ver TEXT, timestamp  TEXT);";
        debug!("Creating table if not exists...");
        let status = conn.execute(query).unwrap();
        debug!("{:?}", status);
        conn
    }

    pub fn get_connection() -> sqlite::Connection {
        Database::ensure_created()
    }

    pub fn get_packages() -> Vec<Package> {
        let query = "SELECT * FROM Packages";
        let conn = Database::get_connection();
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
            let timestamp = String::from(row.read::<&str, _>("timestamp"));
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

    pub fn insert_package(package: &Package) -> bool {
        let query = "INSERT INTO Packages VALUES(?,?,?,?)";
        let conn = Database::get_connection();
        let mut statement = conn.prepare(query).unwrap();
        statement.bind((1, package.name.as_str())).unwrap();
        statement.bind((2, package.base.as_str())).unwrap();
        statement.bind((3, package.ver.as_str())).unwrap();
        statement.bind((4, package.timestamp.as_str())).unwrap();
        statement.next().unwrap() == State::Done
    }

    pub fn package_exists(package: &Package) -> bool {
        let query = "SELECT * FROM Packages WHERE Name = ? LIMIT 1";
        let conn = Database::get_connection();
        let mut statement = conn.prepare(query).unwrap();
        statement.bind((1, package.name.as_str())).unwrap();
        if statement.next().unwrap() == State::Done {
            return false;
        }
        statement.next().unwrap() == State::Done
    }
}
