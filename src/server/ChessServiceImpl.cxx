#include "server/ChessServiceImpl.hxx"

#include <iostream>

#include <grpcpp/grpcpp.h>

Remote::ChessServiceImpl::ChessServiceImpl()
{
}

grpc::Status Remote::ChessServiceImpl::ConnectToServer(
        grpc::ServerContext* context,
        const Proto::Empty* request,
        Proto::ActionResult* response)
{
    std::cout << "Request gotten" << std::endl;
    return grpc::Status::OK;
}
