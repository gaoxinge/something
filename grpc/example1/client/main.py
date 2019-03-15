# -*- coding: utf-8 -*-
import grpc
from google.protobuf import struct_pb2
from example import data_pb2, data_pb2_grpc


def run():
    with grpc.insecure_channel("localhost:5000") as channel:
        stub = data_pb2_grpc.RouterStub(channel)

        # test field rule
        response = stub.Route1(data_pb2.Request1(array=[1, 2, 3], double_value=1))
        print(response.text)

        # test field type
        request2 = data_pb2.Request2()

        # add bytes
        with open("qwer.txt", "rb") as f:
            request2.b = f.read()

        # add enum
        request2.e = data_pb2.SomeEnum.Value("NEWS")

        # add map
        request2.m["a"] = 1
        request2.m["b"] = 2

        # test Any
        NULL_VALUE = struct_pb2.Struct()
        request2.any.Pack(NULL_VALUE)

        # test NullValue

        # test ListValue
        # struct = struct_pb2.Struct()
        # struct_list = struct.get_or_create_list("key5")
        # struct_list.extend([6, "seven", True, False, None])
        # request2.array = struct_list
        request2.array.extend([6, "seven", True, False, None])

        # test nested message
        Bbox1 = data_pb2.Bbox(left=1, top=2, right=3, bottom=4)
        Bbox2 = data_pb2.Bbox(left=2, top=4, right=6, bottom=8)
        request2.bs.extend([Bbox1, Bbox2])

        response = stub.Route2(request2)
        print(response.text)


if __name__ == "__main__":
    run()