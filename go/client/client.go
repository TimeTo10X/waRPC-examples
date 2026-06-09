package main

import (
	"log"
	"sync"

	"github.com/wanime/warpc-go-examples/go/common"
	wrsc "github.com/wanime/warpc-go-examples/schema"
	client "github.com/wanime/warpc/client"
)

var wg sync.WaitGroup

func main() {

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

	resp, status, err := c.CallSync(common.RouteEcho, echo_buff)

	if err != nil {
		log.Fatalf("sync: %v", err)
	}

	if status != 0 {
		log.Fatalf("sync server returned status=0x%02x", status)
	}

	sync_response, _ := wrsc.DecodeEcho(resp)

	log.Printf("sync response: %v\n", sync_response.Message)

	wg.Add(1)

	err = c.CallAsync(common.RouteEcho, echo_buff)

	if err != nil {
		log.Fatalf("async: %v", err)
	}

	wg.Wait()
}
