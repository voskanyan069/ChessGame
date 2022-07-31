#ifndef __IO_QUERY_HXX__
#define __IO_QUERY_HXX__

#include <string>

namespace Pieces
{
    struct Position;
}

class Query
{
public:
    static Query* GetInstance();
    Query(Query const&) = delete;
    void operator=(Query const&) = delete;

private:
    Query();

public:
    void AskPosition(const std::string& msg, Pieces::Position& pos) const;
    bool AskForReady() const;

private:
    std::string createMsgBool(const std::string& msg, bool defaultVal) const;
    bool processMsgBool(const std::string& input, bool& value) const;
};

#endif // __IO_QUERY_HXX__
