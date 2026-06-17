#include "../../../schema/exmp.hpp"

#include <wanime-server-sdk/server.h>

#include <wanime-sdk/imports.hpp>
#include <wanime-server-sdk/framework/server.hpp>

using pipelines::tu;

RPC(echo, Routes::Echo | tu) {
    const auto& rq = request | exmp::as<exmp::Echo>;

    rq | exmp::print;

    w exmp::make_echo(out, cap, rq.message).value();

    return warpc::Success;
}

RPC(calc, Routes::Calc | tu) {
    const auto& rq = request | exmp::as<exmp::CalcRequest>;

    rq | exmp::print;

    double result = 0;
    switch (rq.op) {
    case exmp::Op::Add:
        result = rq.a + rq.b;
        break;
    case exmp::Op::Sub:
        result = rq.a - rq.b;
        break;
    case exmp::Op::Mul:
        result = rq.a * rq.b;
        break;
    case exmp::Op::Div:
        if (rq.b == 0) {
            w exmp::make_calc_error(out, cap, "Division by zero!").value();
            return warpc::Failure;
        }

        result = rq.a / rq.b;
        break;
    }

    w exmp::make_calc_response(out, cap, result).value();

    return warpc::Success;
}
