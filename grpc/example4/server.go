package main

import (
	"golang.org/x/net/context"
	"example3/proto"
	"net"
	"log"
	"google.golang.org/grpc"
)

type router struct {}

func (s *router) Route(ctx context.Context, request *proto.Request) (*proto.Response, error){
	return &proto.Response{Text: request.Text}, nil
}

func main() {
	listen, err := net.Listen("tcp", "localhost:5000")
	if err != nil {
		log.Fatal(err)
	}

	s := grpc.NewServer()
	proto.RegisterRouterServer(s, &router{})
	s.Serve(listen)
}