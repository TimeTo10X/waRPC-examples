/*
 * Copyright (c) 2026 wanime.io. All Rights Reserved.
 */

#include <wanime-client-sdk/client.h>

#include <wanime-sdk/utils.hpp>

#include "../schema/messages.hpp"
#include "../sync.hpp"

/*
 * Basic example of calc API using waRPC async API
 *
 * Github:
 *     https://github.com/TimeTo10X/waRPC-examples/async_calc
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
        /* Destroy client instance if initialization failed */
        std::println("Failed to init client: {}", st);
        wa_client::destroy_client(client);
        return -1;
    }

    st = wa_client::connect(*client, options.server_ip, options.server_port);

    if (failed(st)) {
        /* Destroy client instance if connection failed */
        std::println("Connection failed: {}", st);
        wa_client::destroy_client(client);
        return -1;
    }

    calc::PmrVec calc_rq;
    calc::make_calc_request(calc_rq, 7, 7, calc::Op::Add);

    auto payload_span = calc_rq | calc::as_span;

    const auto rpc_request = protocol::warpc::make_rpc_request(protocol::warpc::RpcType::Rpc, 0, payload_span);

    st = wa_client::call_async(*client, rpc_request);
    std::println("Sent RPC request");

    if (failed(st)) {
        std::println("RPC request failed: {}", st);
        wa_client::destroy_client(client);
        return -1;
    }

    std::println("Waiting for response");

    g_sync.wait();

    wa_client::destroy_client(client);
}
