package ex_client

import wrsc "../schema"
import "core:fmt"
import client "wanime:client"

OK :: client.WaRpcStatus(0)

main :: proc() {
	c, opts := client.create_client_from_args()
	defer client.client_destroy(c)

	client.client_init(c)
	conn_st := client.client_connect(c, opts.server_ip_ptr, opts.server_port)

	if conn_st != OK {
		fmt.println("failed to connect!")
		return
	}

	echo: wrsc.Echo = wrsc.Echo {
		message = "東京へよこそ",
	}

	out_buf: [dynamic]u8
	wrsc.echo_encode(&out_buf, echo)

	resp_buff := make([dynamic]u8, len(out_buf))
	defer delete(resp_buff)

	in_len := len(out_buf)
	out_len := len(out_buf)

	status := client.client_call_sync(
		c,
		0,
		raw_data(out_buf),
		in_len,
		raw_data(resp_buff),
		&out_len,
	)

	if status != OK {
		fmt.println("Failed to send sync request")
		return
	}

	fmt.println("Response length:", out_len)
	x := client.client_call_async(c, 0, raw_data(out_buf), in_len)

	if x != OK {
		fmt.println("Failed to send async request")
		return
	}

	client.getchar()
}
