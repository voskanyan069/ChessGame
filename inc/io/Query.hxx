#ifndef __IO_QUERY_HXX__
#define __IO_QUERY_HXX__

#include "utils/Types.hxx"
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
    Pieces::PawnReplacements AskPawnReplacement() const;

private:
    void printUsername() const;
    std::string createMsgBool(const std::string& msg, bool defaultVal) const;
    bool processMsgBool(const std::string& input, bool& value) const;
    bool processPawnReplacement(const std::string& input, int& value) const;
};

#endif // __IO_QUERY_HXX__
