extern crate pretty_env_logger;
#[macro_use]
extern crate log;
extern crate tar;
pub mod package;
use std::fs::File;

use crate::package::package::Package;
use flate2::read::GzDecoder;
use std::io::Read;
use std::path::PathBuf;
use structopt::StructOpt;
use tar::Archive;

/**
 *
 *  Plan of action:
 *  1 - Need to parse arguments (ie, install, upgrade, remove)
 *  2 - Need to create a package layout so we can install, upgrade, or remove.
 *      - Need to find out relevant information and naming scheme
 *
 */

#[derive(StructOpt, Debug)]
struct Cli {
    #[structopt(short, long)]
    install: Option<PathBuf>,
    #[structopt(short, long)]
    remove: Option<String>,
    #[structopt(short, long)]
    update: Option<PathBuf>,
    #[structopt(short, long)]
    verbose: Option<bool>,
}

fn main() {
    pretty_env_logger::init();
    let args = Cli::from_args();
    let install_arg: Option<PathBuf> = args.install;
    let remove_arg: Option<String> = args.remove;
    let update_arg: Option<PathBuf> = args.update;
    let verbose_arg: Option<bool> = args.verbose;

    if let Some(install) = install_arg {
        let path = install;
        let file = File::open(path.as_os_str().to_str().unwrap()).unwrap();
        let gz = GzDecoder::new(file);
        let mut a = Archive::new(gz);
        for file in a.entries().unwrap() {
            let mut file = file.unwrap();
            let path_str = file.path().unwrap();
            let path = path_str.to_str().unwrap();
            match path {
                ".PKGINFO" => {
                    let mut buffer = String::new();
                    file.read_to_string(&mut buffer);
                    let deserialized: Package = serde_json::from_str(&buffer).unwrap();
                    println!("{:?}", deserialized);
                }
                _ => {}
            }
        }
        assert!(false, "Not implemented");
    }

    if let Some(remove_arg) = remove_arg {
        assert!(false, "Not implemented");
    }

    if let Some(update_arg) = update_arg {
        assert!(false, "Not implemented");
    }

    if let Some(verbose_arg) = verbose_arg {
        assert!(false, "Not implemented");
    }
}
