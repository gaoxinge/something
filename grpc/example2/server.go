package main

import (
	"golang.org/x/net/context"
	"example2/helloworld"
	"net"
	"log"
	"google.golang.org/grpc"
)

type greeter struct {}

func (s *greeter) SayHello(ctx context.Context, request *helloworld.HelloRequest) (*helloworld.HelloReply, error){
	return &helloworld.HelloReply{Message: request.Name}, nil
}

func main() {
	listen, err := net.Listen("tcp", "localhost:50051")
	if err != nil {
		log.Fatal(err)
	}

	s := grpc.NewServer()
	helloworld.RegisterGreeterServer(s, &greeter{})
	s.Serve(listen)
}
