extern crate pretty_env_logger;
#[macro_use]
extern crate log;
extern crate tar;
pub mod db;
pub mod package;
use crate::db::db::Database;
use crate::package::package::Package;
use flate2::read::GzDecoder;
use std::env;
use std::fs::File;
use std::io::Read;
use std::path::PathBuf;
use structopt::StructOpt;
use tar::Archive;

/**
 *
 *  Plan of action::
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
    #[structopt(short)]
    verbose: bool,
    #[structopt(short, long)]
    directory: Option<PathBuf>,
}

fn main() {
    pretty_env_logger::init();
    let args = Cli::from_args();
    let install_arg: Option<PathBuf> = args.install;
    let remove_arg: Option<String> = args.remove;
    let update_arg: Option<PathBuf> = args.update;
    let directory_arg: Option<PathBuf> = args.directory;
    let _verbose_arg: bool = args.verbose;
    Database::ensure_created();

    if let Some(install) = install_arg {
        //        assert!(false, "Not implemented -- Installing to default path");
        let path = install;
        let file = File::open(path.as_os_str().to_str().unwrap()).unwrap();
        let gz = GzDecoder::new(&file);
        let mut a = Archive::new(gz);
        let mut can_install: bool = false;
        let mut pkg = Package::default();
        for file in a.entries().unwrap() {
            let mut file = file.unwrap();
            let path_str = file.path().unwrap();
            let path = path_str.to_str().unwrap();
            match path {
                ".PKGINFO" => {
                    let mut buffer = String::new();
                    let res: Package = match file.read_to_string(&mut buffer) {
                        Ok(_) => {
                            let pack: Package = match serde_json::from_str(&buffer) {
                                Ok(pkg) => pkg,
                                Err(err) => panic!("Could not parse .PKGINFO - {}", err),
                            };
                            pack
                        }
                        Err(err) => panic!("Could not parse .PKGINFO - {}", err),
                    };
                    if Database::package_exists(&res) {
                        panic!("Package already exists. Perhaps you meant to upgrade?");
                    }
                    pkg = res;
                    can_install = true;
                    break;
                }
                _ => {}
            };
        }
        if !can_install {
            panic!("Not installing package - no .PKGINFO?");
        }
        let mut dst = String::from(format!("{}/.local/", env::var("HOME").unwrap()));
        if let Some(directory_arg) = directory_arg {
            dst = String::from(directory_arg.to_str().unwrap());
        }
        info!("unpacking to {}", dst);
        let target = File::open(path.to_str().unwrap()).unwrap();
        let dec = GzDecoder::new(&target);
        a = Archive::new(dec);
        for file in a.entries().unwrap() {
            let mut file = file.unwrap();
            let path_str = file.path().unwrap();
            let path = path_str.to_str().unwrap();
            match path {
                ".PKGINFO" => {}
                ".TREE" => {}
                _ => {
                    file.unpack_in(&dst).unwrap();
                }
            }
        }
        info!("Updating database...");
        Database::insert_package(&pkg);
        info!("Done..");
    }

    if let Some(_remove_arg) = remove_arg {
        assert!(false, "Not implemented -- removing");
    }

    if let Some(_update_arg) = update_arg {
        assert!(false, "Not implemented -- updating");
    }
}
