package main

import (
	"log"
	"example2/helloworld"
	"golang.org/x/net/context"
	"google.golang.org/grpc"
)

func main() {
	conn, err := grpc.Dial("localhost:50051", grpc.WithInsecure())
	if err != nil {
		log.Fatal(err)
	}

	defer conn.Close()

	client := helloworld.NewGreeterClient(conn)

	response, err := client.SayHello(context.Background(), &helloworld.HelloRequest{Name: "hello world"})
	if err != nil {
		log.Fatal(err)
	}

	log.Print(response.Message)
}
