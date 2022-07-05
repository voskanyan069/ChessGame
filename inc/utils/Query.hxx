#ifndef __UTILS_QUERY_HXX__
#define __UTILS_QUERY_HXX__

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
};

#endif // __UTILS_QUERY_HXX__
