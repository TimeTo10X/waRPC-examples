
#include <wanime-client-sdk/client.h>
#include <wanime-sdk/framework/utils.h>
#include <wanime-sdk/tokyo_main.h>
#include <wanime-sdk/utils/ctime.h>
#include <wanime-sdk/warpc/status.h>

#include <tokyo/tokyo_main.hxx>

#include "../../schema/exmp.hpp"
#include "../sync/sync.h"

namespace _sync {

auto run_echo(wa_client::Client* c) -> void {
    exmp::Echo message{.message = "waRPC Echo ^_^"};
    exmp::PmrVec response;

    const auto bytes = message | exmp::encode;
    const auto payload = bytes | exmp::as_span;

    auto sync_rpc_request_st = wa_client::call_sync(*c, Routes::Echo | pipelines::tu, payload, response);

    if (sync_rpc_request_st.failed()) {
        std::println("RPC request failed! status: [{}]", sync_rpc_request_st.code());
    }

    const auto echo_resp_decoded = response | exmp::as<exmp::Echo>;

    echo_resp_decoded | exmp::print;
}

auto run_calc(wa_client::Client* c) -> void {
    exmp::CalcRequest message{.a = 6, .b = 7, .op = exmp::Op::Mul};

    exmp::PmrVec response;

    const auto bytes = message | exmp::encode;
    const auto payload = bytes | exmp::as_span;

    auto sync_rpc_request_st = wa_client::call_sync(*c, Routes::Calc | pipelines::tu, payload, response);

    if (sync_rpc_request_st.failed()) {
        std::println("RPC request failed! status: [{}]", sync_rpc_request_st.code());
    }

    const auto calc_resp_decoded = response | exmp::as<exmp::CalcResponse>;

    calc_resp_decoded | exmp::print;
}

auto run_calc_div_0(wa_client::Client* c) -> void {
    exmp::CalcRequest message{.a = 6, .b = 0, .op = exmp::Op::Div};

    exmp::PmrVec response;

    const auto bytes = message | exmp::encode;
    const auto payload = bytes | exmp::as_span;

    auto sync_rpc_request_st = wa_client::call_sync(*c, Routes::Calc | pipelines::tu, payload, response);

    if (sync_rpc_request_st.failed()) {
        std::println("RPC request failed! status: [{}]", sync_rpc_request_st.code());

        const auto calc_err_decoded = response | exmp::as<exmp::CalcError>;
        calc_err_decoded | exmp::print;
        return;
    }

    const auto calc_resp_decoded = response | exmp::as<exmp::CalcResponse>;

    calc_resp_decoded | exmp::print;
}

}  // namespace _sync

namespace _async {

auto run_echo(wa_client::Client* c) -> void {
    exmp::Echo message{.message = "waRPC Echo ^_^"};

    const auto bytes = message | exmp::encode;
    const auto payload = bytes | exmp::as_span;

    auto async_rpc_request_st = wa_client::call_async(*c, Routes::Echo | pipelines::tu, payload);

    if (async_rpc_request_st.failed()) {
        std::println("RPC request failed! status: [{}]", async_rpc_request_st.code());
    }
}

auto run_calc(wa_client::Client* c) -> void {
    exmp::CalcRequest message{.a = 6, .b = 7, .op = exmp::Op::Mul};

    const auto bytes = message | exmp::encode;
    const auto payload = bytes | exmp::as_span;

    auto async_rpc_request_st = wa_client::call_async(*c, Routes::Calc | pipelines::tu, payload);

    if (async_rpc_request_st.failed()) {
        std::println("RPC request failed! status: [{}]", async_rpc_request_st.code());
    }
}

auto run_calc_div_0(wa_client::Client* c) -> void {
    exmp::CalcRequest message{.a = 6, .b = 0, .op = exmp::Op::Div};

    const auto bytes = message | exmp::encode;
    const auto payload = bytes | exmp::as_span;

    auto async_rpc_request_st = wa_client::call_async(*c, Routes::Calc | pipelines::tu, payload);

    if (async_rpc_request_st.failed()) {
        std::println("RPC request failed! status: [{}]", async_rpc_request_st.code());
    }
}

}  // namespace _async

tokyo {
    __time(init);
    const auto [c, opts] = setup_tokyo_client(argc, argv);

    wa_client::init(*c);
    time__(init);

    __time(connect);
    const auto connection_st = wa_client::connect(*c, opts.server_ip, opts.server_port);

    if (connection_st.failed()) {
        std::println("Failed to connect! status: [{}]", connection_st.code());
        return connection_st.code();
    }
    time__(connect);

    _sync::run_echo(c);
    _sync::run_calc(c);
    _sync::run_calc_div_0(c);

    _async::run_echo(c);
    _async::run_calc(c);
    _async::run_calc_div_0(c);

    wait_async_exec.wait();

    _ 0;
}
