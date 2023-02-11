extern crate pretty_env_logger;
#[macro_use]
extern crate log;
extern crate tar;
pub mod package;
use std::fs::File;

use crate::package::package::Package;
use tar::Archive;
fn main() {
    pretty_env_logger::init();
    println!("Hello, world!");
    info!("This is a log");
    let p = Package::new(
        String::from("test"),
        String::from("test"),
        String::from("123"),
    );

    let file = File::open(p.get_package_name()).unwrap();
    let mut tar = Archive::new(file);
    for file in tar.entries().unwrap() {
        let file = file.unwrap();
        println!("{:?}", file.header().path().unwrap());
    }
}
