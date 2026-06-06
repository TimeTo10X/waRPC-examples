package ex_server

import server "wanime:server"

main :: proc() {
	s, opts := server.create_server_from_args()

	server.c_server_start(s)
	defer server.c_server_stop(s)
	defer server.c_server_destroy(s)

	server.getchar()
}
