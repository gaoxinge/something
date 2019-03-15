```
> pip install grpcio-tools
> cd example
> python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. ./data.proto
```