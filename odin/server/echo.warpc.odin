package ex_server

import routes "../common"
import wrsc "../schema"
import server "wanime:server"

handle_echo :: proc(id: u16, req: []u8, out: ^[dynamic]u8) -> i16 {
	echo, err := wrsc.echo_decode(req)

	if err != nil {
		return 0
	}

	echo_response := wrsc.Echo {
		message = echo.message,
	}

	wrsc.echo_encode(out, echo_response)

	return 0
}

@(init)
__echo :: proc "contextless" () {
	server.register_rpc(routes.ROUTE_ECHO, handle_echo)
}
