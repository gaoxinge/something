# -*- coding: utf-8 -*-
import grpc
import time
from concurrent import futures
from proto import data_pb2, data_pb2_grpc


class Router(data_pb2_grpc.RouterServicer):

    def Route(self, request, context):
        return data_pb2.Response(text=request.text)


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
