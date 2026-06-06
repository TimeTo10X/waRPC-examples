#include "../../../schema/exmp.hpp"

#include <wanime-server-sdk/server.h>

#include <wanime-sdk/imports.hpp>
#include <wanime-server-sdk/framework/server.hpp>

using pipelines::tu;

RPC(echo, Routes::Echo | tu) {
    const auto& rq = request | exmp::as<exmp::Echo>;

    rq | exmp::print;

    exmp::make_echo(out, rq.message);

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
            exmp::make_calc_error(out, "Division by zero!");
            return warpc::Failure;
        }

        result = rq.a / rq.b;
        break;
    }

    exmp::make_calc_response(out, result);

    return warpc::Success;
}
