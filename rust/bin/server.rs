use exmp::{self, handlers as _};
use warpc::{Options, Server, init_dispatch};

fn main() {
    init_dispatch();

    let cert_dir = std::env::current_dir().unwrap().join("certs");

    let srv = Server::new(Options {
        cert_file: cert_dir.join("localhost-ec.pem").to_string_lossy().into(),
        key_file: cert_dir.join("localhost-ec.key").to_string_lossy().into(),
        key_password: String::new(),
        port: 6666,
    })
    .expect("create server");

    srv.start();

    let (tx, rx) = std::sync::mpsc::channel();
    ctrlc::set_handler(move || {
        let _ = tx.send(());
    })
    .expect("install ctrl-c handler");

    rx.recv().expect("recv");

    println!("shutting down");

    srv.stop();
}
