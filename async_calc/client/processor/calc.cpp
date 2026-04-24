/*
 * Copyright (c) 2026 wanime.io. All Rights Reserved.
 */

#include <print>
#include <wanime-client-sdk/framework/client.hpp>
#include <wanime-client-sdk/rpc/rpc.hpp>

#include "../../schema/messages.hpp"
#include "../../sync.hpp"

RPC(calc_api, calc::Routes::Calc | calc::tu) {
    /* Parse response from server */
    const auto& calc_response = response | calc::as<calc::CalcResponse>;

    /* Process response from server */
    std::println("Result: {}", calc_response.result);

    /* Decrement latch */
    g_sync.count_down();
    return TaskStatus::SUCCESS;
}
