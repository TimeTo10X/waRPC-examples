package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"
	"path/filepath"
	"syscall"

	waserver "github.com/wanime/warpc/server"
)

func main() {
	certDir, _ := filepath.Abs("../certs")
	srv, err := waserver.NewServer(waserver.Options{
		CertFile: filepath.Join(certDir, "localhost-ec.pem"),
		KeyFile:  filepath.Join(certDir, "localhost-ec.key"),
		Port:     6666,
	})

	if err != nil {
		log.Fatalf("NewServer: %v", err)
	}

	defer srv.Stop()
	defer srv.Close()

	if err := srv.Start(); err != nil {
		log.Fatalf("Start: %v", err)
	}

	sigs := make(chan os.Signal, 1)
	signal.Notify(sigs, os.Interrupt, syscall.SIGTERM)

	<-sigs

	fmt.Println("shutting down")
}
