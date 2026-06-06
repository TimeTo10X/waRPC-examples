use warpc::{STATUS_SUCCESS, rpc};

#[rpc(id = 0)]
pub fn echo(req: &[u8]) -> (Vec<u8>, i16) {
    println!("Received: {:?}", req);
    (req.to_vec(), STATUS_SUCCESS)
}
