#include "client/ChessClient.hxx"

#include <grpcpp/grpcpp.h>

Remote::ChessClient::ChessClient(const std::string& hostname)
    : m_stub(Proto::ChessServer::NewStub(grpc::CreateChannel(
                    hostname, grpc::InsecureChannelCredentials())))
{
}

void Remote::ChessClient::ConnectToServer()
{
    grpc::ClientContext ctx;
    Proto::Empty request;
    Proto::ActionResult response;
    grpc::Status status = m_stub->ConnectToServer(&ctx, request, &response);
    if (status.ok())
    {
        std::cout << "ActionResult: {\n\tcode: " << response.success()
            << "\n\terrmsg: \"" << response.errmsg() << "\"\n}" << std::endl;
    }
}
