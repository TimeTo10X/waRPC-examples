package main

import (
	"github.com/wanime/warpc-go-examples/go/common"
	waserver "github.com/wanime/warpc/server"
	"log"
)

func init() {
	waserver.RegisterRpcHandler(common.RouteEcho, func(req []byte) ([]byte, int16) {
		log.Print("[echo]\n")
		return append([]byte(nil), req...), waserver.StatusSuccess
	})
}
