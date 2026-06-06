package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	wrsc "github.com/wanime/warpc-go/schema"
	client "github.com/wanime/warpc/client"
)

const RouteEcho uint16 = 0

func main() {
	var wg sync.WaitGroup

	client.RegisterRpcHandler(RouteEcho, func(req []byte, status int16) (rt_status int16) {
		echo, err := wrsc.DecodeEcho(req)

		if err != nil {
			log.Printf("[echo] Async echo request failed!")
		}

		log.Printf("[echo] %d message: %v", len(req), echo.Message)
		wg.Done()
		return 0
	})

	c, err := client.NewClient(client.Options{
		ServerIP:   "::1",
		ServerPort: 6666,
	})

	if err != nil {
		log.Fatal(err)
	}

	if err := c.Connect(); err != nil {
		log.Fatal(err)
	}

	echo_buff := []byte{}

	echo_request := wrsc.Echo{Message: "dw"}

	wrsc.MakeEcho(&echo_buff, &echo_request)

	resp, status, err := c.CallSync(RouteEcho, echo_buff)

	if err != nil {
		log.Fatalf("sync: %v", err)
	}

	if !client.StatusIsSuccess(status) {
		log.Fatalf("sync server returned status=0x%02x", status)
	}

	sync_response, _ := wrsc.DecodeEcho(resp)

	fmt.Printf("sync response: %v\n", sync_response.Message)

	wg.Add(1)

	err = c.CallAsync(RouteEcho, echo_buff)

	if err != nil {
		log.Fatalf("async: %v", err)
	}

	wg.Wait()
}


