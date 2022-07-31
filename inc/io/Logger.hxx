#ifndef __IO_LOGGER_HXX__
#define __IO_LOGGER_HXX__

#include "pieces/BasePiece.hxx"
#include "utils/Exception.hxx"

#include <boost/format.hpp>

#include <ostream>

namespace Chess
{
    class Board;
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
    void PrintEndl() const;
    void PrintHelp(const std::string& helpMsg) const;
    void PrintBoard() const;
    void SetStream(std::ostream* os);

public:
    void Print(const Utils::Exception& error) const;
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
    Chess::Board* m_board;
};

#endif // __IO_LOGGER_HXX__
