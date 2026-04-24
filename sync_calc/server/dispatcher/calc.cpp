#include <wanime-server-sdk/framework/server.hpp>
#include <wanime-server-sdk/rpc/rpc.hpp>

#include "../../schema/messages.hpp"

RPC(calc_api, 0) {
    const auto& calc_req = request | calc::as<calc::CalcRequest>;

    double result = 0;

    calc_req | calc::print;

    switch (calc_req.op) {
    case calc::Op::Add:
        result = calc_req.a + calc_req.b;
        break;
    case calc::Op::Sub:
        result = calc_req.a - calc_req.b;
        break;
    case calc::Op::Mul:
        result = calc_req.a * calc_req.b;
        break;
    case calc::Op::Div:
        if (calc_req.b == 0)
            return TaskStatus::FAILED;
        result = calc_req.a / calc_req.b;
        break;
    }

    std::println("Result: {}", result);
    calc::make_calc_response(out, result);
    return TaskStatus::SUCCESS;
}
