#include "server/ChessServer.hxx"
#include "server/ChessServiceImpl.hxx"

#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>

Remote::ChessServer::ChessServer()
{
}

void Remote::ChessServer::RunServer(int port)
{
    std::string address("0.0.0.0:" + std::to_string(port));
    Remote::ChessServiceImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << address << std::endl;
    server->Wait();
}
