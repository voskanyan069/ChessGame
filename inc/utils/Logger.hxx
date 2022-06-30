#ifndef __UTILS_LOGGER_HXX__
#define __UTILS_LOGGER_HXX__

#include <boost/format.hpp>

#include <ostream>

namespace Pieces
{
    class BasePiece;
}

typedef enum
{
    INFO,
    WARN,
    ERROR
} MessageType;

class Logger
{
public:
    static Logger* GetInstance();
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

private:
    Logger();

public:
    void SetStream(std::ostream* os);
    void PrintBoard() const;

public:
    template<typename... Arguments>
    void Print(const MessageType& type, const std::string& fmt,
            Arguments&&... args) const
    {
        setConsoleColor(type);
        *m_os <<  boost::str((boost::format(fmt) % ... % args));
        resetConsole();
    }

private:
    void setConsoleColor(const MessageType& type) const;
    void resetConsole() const;
    void printLetters(bool line=true) const;
    void printPieceChar(const Pieces::BasePiece* piece) const;
    void printPieces(int lineIdx) const;
    void printLines() const;

private:
    std::ostream* m_os;
};

#endif // __UTILS_LOGGER_HXX__
