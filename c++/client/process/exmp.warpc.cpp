#include "../../../schema/exmp.hpp"

#include <wanime-client-sdk/client.h>

#include <wanime-client-sdk/framework/client.hpp>
#include <wanime-sdk/imports.hpp>

using pipelines::tu;

RPC(echo, Routes::Echo | tu) {
    const auto& rs = response | exmp::as<exmp::Echo>;

    rs | exmp::print;

    return warpc::Success;
}

RPC(calc, Routes::Calc | tu) {
    if (status.failed()) {
        const auto& err = response | exmp::as<exmp::CalcError>;

        err | exmp::print;

        return status;
    }

    const auto& rs = response | exmp::as<exmp::CalcResponse>;

    rs | exmp::print;

    return warpc::Success;
}
