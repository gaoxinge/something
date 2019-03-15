# -*- coding: utf-8 -*-
import grpc
import time
from concurrent import futures
from example import data_pb2, data_pb2_grpc


class Router(data_pb2_grpc.RouterServicer):

    def Route1(self, request, context):
        # test repeated
        array = request.array
        print("repeated:", array)

        # test oneof
        double_value = request.double_value
        print("oneof:", double_value)

        return data_pb2.Response(text="Hello World!")

    def Route2(self, request, context):
        # print bytes
        b = request.b
        print("bytes:", b)

        # print enum
        e = request.e
        print("enum:", e)

        # print map
        m = request.m
        print("map:", m)

        # print Any
        any = request.any
        print("any:", any)

        # print NullValue
        null = request.null
        print("nullvalue:", null)

        # print ListValue
        array = request.array
        print("listvalue:", array.values)

        # print nested message
        bs = request.bs
        print("nested message:", bs)

        return data_pb2.Response(text="Hello World!")


def run():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=4))
    data_pb2_grpc.add_RouterServicer_to_server(Router(), server)
    server.add_insecure_port("localhost:5000")
    server.start()
    try:
        while True:
            time.sleep(60 * 60 * 24)
    except KeyboardInterrupt:
        server.stop(0)


if __name__ == "__main__":
    run()
