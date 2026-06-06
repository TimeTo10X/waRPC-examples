use warpc::{STATUS_FAILED, STATUS_SUCCESS, rpc};

#[rpc(id = 1)]
pub fn compute_calc(req: &[u8]) -> (Vec<u8>, i16) {
    let id = match std::str::from_utf8(req) {
        Ok(s) => s,
        Err(_) => return (Vec::new(), STATUS_FAILED),
    };
    let resp = format!("user:{}", id).into_bytes();
    (resp, STATUS_SUCCESS)
}
