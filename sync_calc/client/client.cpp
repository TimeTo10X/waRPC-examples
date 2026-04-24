/*
 * Copyright (c) 2026 wanime.io. All Rights Reserved.
 */
#include <wanime-client-sdk/client.h>

#include <wanime-sdk/utils.hpp>

#include "../schema/messages.hpp"
/*
 * Basic example of calc API using waRPC sync API
 *
 * Github:
 *     https://github.com/TimeTo10X/waRPC-examples/sync_calc
 * Docs:
 *     https://wanime.io/warpc
 *     https://wanime.io/warpc/architecture
 *     https://wanime.io/warpc/api
 */
auto main(int argc, char* argv[]) -> int {
    const auto options = wa_client::parse_options(std::span(argv, argc));
    auto* client = wa_client::create_client(options);
    auto st = wa_client::init_client(*client);

    if (failed(st)) {
        std::println("Failed to init client: {}", st);
        wa_client::destroy_client(client);
        return -1;
    }

    st = wa_client::connect(*client, options.server_ip, options.server_port);

    if (failed(st)) {
        std::println("Connection failed: {}", st);
        wa_client::destroy_client(client);
        return -1;
    }

    calc::PmrVec calc_rq;
    calc::make_calc_request(calc_rq, 7, 7, calc::Op::Add);

    const auto payload_span = calc_rq | calc::as_span;

    const auto rpc_request =
        protocol::warpc::make_rpc_request(protocol::warpc::RpcType::Rpc, calc::Routes::Calc | calc::tu, payload_span);

    calc::PmrVec response;

    std::println("Sending RPC request");
    auto task_st = wa_client::call_sync(*client, rpc_request, response);
    std::println("Received response from server");

    if (failed(task_st)) {
        std::println("RPC request failed: {}", st);
        wa_client::destroy_client(client);
        return -1;
    }

    const auto calc_result = response | calc::as<calc::CalcResponse>;

    calc_result | calc::print;

    wa_client::destroy_client(client);
}
