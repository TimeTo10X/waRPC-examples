package ex_client

import routes "../common"
import wrsc "../schema"
import "core:fmt"
import client "wanime:client"

handle_echo :: proc(route: u16, data: []u8, status: i16) -> i16 {
	echo, _ := wrsc.echo_decode(data)

	fmt.printfln(
		"Echo response received! Status: %d, Size: %d, Body: %v",
		status,
		len(data),
		echo.message,
	)
	return 0
}

@(init)
__echo :: proc "contextless" () {
	client.register_rpc(routes.ROUTE_ECHO, handle_echo)
}
