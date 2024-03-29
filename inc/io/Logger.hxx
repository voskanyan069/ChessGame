#ifndef __IO_LOGGER_HXX__
#define __IO_LOGGER_HXX__

#include "pieces/BasePiece.hxx"
#include "utils/Exception.hxx"

#include <boost/format.hpp>

#include <ostream>

namespace Chess
{
    class Board;
    class GameMgr;
}

typedef enum
{
    INFO,
    WARN,
    ERROR
} MessageType;

typedef enum
{
    WHITE,
    BLACK
} BackgroundType;

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

public:
    bool IsWhiteTop() const;
    void ReverseBoard();
    void Print(const Utils::Exception& error) const;
    void PrintEndl() const;
    void PrintHelp(const std::string& helpMsg) const;
    void PrintBoard() const;
    template<typename... Arguments>
    void Print(const MessageType& type, const std::string& fmt,
            Arguments&&... args) const
    {
        setConsoleColor(type);
        *m_os << boost::str((boost::format(fmt) % ... % args)) << std::endl;
        resetConsole();
    }

private:
    void setConsoleColor(const MessageType& type) const;
    void setConsoleBackground(const BackgroundType& type) const;
    BackgroundType reverseBackgroundColor() const;
    void resetConsole() const;
    void printViewersCount() const;
    void printLetters(bool line=true) const;
    void printPieceChar(const Pieces::BasePiece* piece) const;
    void printPieces(int lineIdx) const;
    void printLastMove(int lineIdx) const;
    void printLine(int lineIdx) const;
    void printLinesWT() const;
    void printLinesBT() const;
    void printLines() const;

private:
    bool m_bWhiteTop;
    std::ostream* m_os;
    Chess::Board* m_board;
    Chess::GameMgr* m_gameMgr;
};

#endif // __IO_LOGGER_HXX__
