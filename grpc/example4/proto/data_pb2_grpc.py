# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import data_pb2 as data__pb2


class RouterStub(object):
  # missing associated documentation comment in .proto file
  pass

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.Route = channel.unary_unary(
        '/proto.Router/Route',
        request_serializer=data__pb2.Request.SerializeToString,
        response_deserializer=data__pb2.Response.FromString,
        )


class RouterServicer(object):
  # missing associated documentation comment in .proto file
  pass

  def Route(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_RouterServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'Route': grpc.unary_unary_rpc_method_handler(
          servicer.Route,
          request_deserializer=data__pb2.Request.FromString,
          response_serializer=data__pb2.Response.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'proto.Router', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))