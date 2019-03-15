package main

import (
	"log"
	"golang.org/x/net/context"
	"google.golang.org/grpc"
	"example3/proto"
)

func main() {
	conn, err := grpc.Dial("localhost:5000", grpc.WithInsecure())
	if err != nil {
		log.Fatal(err)
	}

	defer conn.Close()

	client := proto.NewRouterClient(conn)

	response, err := client.Route(context.Background(), &proto.Request{Text: "hello world"})
	if err != nil {
		log.Fatal(err)
	}

	log.Print(response.Text)
}