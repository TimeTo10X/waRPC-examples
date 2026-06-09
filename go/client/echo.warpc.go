package main

import (
	"log"

	"github.com/wanime/warpc-go-examples/go/common"
	wrsc "github.com/wanime/warpc-go-examples/schema"
	client "github.com/wanime/warpc/client"
)

func init() {
	client.RPC(client.Route(common.RouteEcho), func(req []byte, status int16) (rt_status int16) {
		echo, err := wrsc.DecodeEcho(req)

		if err != nil {
			log.Printf("[echo] Async echo request failed!")
		}

		log.Printf("[echo] %d message: %v", len(req), echo.Message)
		wg.Done()
		return 0
	})
}
