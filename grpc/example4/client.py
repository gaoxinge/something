# -*- coding: utf-8 -*-
import grpc
from proto import data_pb2, data_pb2_grpc


def run():
    with grpc.insecure_channel("localhost:5000") as channel:
        stub = data_pb2_grpc.RouterStub(channel)
        response = stub.Route(data_pb2.Request(text="Hello World"))
        print(response.text)


if __name__ == "__main__":
    run()
