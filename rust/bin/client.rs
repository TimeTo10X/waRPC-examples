use warpc::{Client, ClientOptions, is_success};

fn main() {
    let c = Client::new(ClientOptions {
        server_ip: "::1".into(),
        server_port: 6666,
    })
    .expect("create client");

    c.connect().expect("connect");

    println!("Connected!");

    let (resp, status) = c.call_sync(0, b"Hello sync!").expect("call_sync");

    println!("Response: {:?}, {status}", resp);

    assert!(is_success(status), "echo status=0x{:02x}", status);

    println!("echo:       {}", String::from_utf8_lossy(&resp));
}
