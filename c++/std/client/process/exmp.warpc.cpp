#include "../../../schema/exmp.hpp"

#include <wanime-client-sdk/client.h>

#include <wanime-client-sdk/framework/client.hpp>
#include <wanime-sdk/imports.hpp>

#include "../../sync/sync.h"

using pipelines::tu;

RPC(echo, Routes::Echo | tu) {
    const auto& rs = response | exmp::as<exmp::Echo>;

    rs | exmp::print;

    wait_async_exec.count_down();

    return warpc::Success;
}

RPC(calc, Routes::Calc | tu) {
    if (status.failed()) {
        const auto& err = response | exmp::as<exmp::CalcError>;

        err | exmp::print;

        wait_async_exec.count_down();

        return status;
    }

    const auto& rs = response | exmp::as<exmp::CalcResponse>;

    rs | exmp::print;

    wait_async_exec.count_down();

    return warpc::Success;
}
