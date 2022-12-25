#include "io/Logger.hxx"
#include "chess/Board.hxx"
#include "chess/GameMgr.hxx"
#include "pieces/BasePiece.hxx"
#include "pieces/Pawn.hxx"
#include "utils/Defines.hxx"
#include "utils/Types.hxx"

#include <iostream>

Logger* Logger::GetInstance()
{
    static Logger* instance = new Logger();
    return instance;
}

Logger::Logger()
    : m_bWhiteTop(false)
    , m_os(&std::cout)
    , m_board(Chess::Board::GetInstance())
    , m_gameMgr(Chess::GameMgr::GetInstance())
{
}

void Logger::setConsoleColor(const MessageType& type) const
{
    switch (type)
    {
    case INFO:
        {
            *m_os << INFO_CONSOLE;
            break;
        }
    case WARN:
        {
            *m_os << WARN_CONSOLE;
            break;
        }
    case ERROR:
        {
            *m_os << ERROR_CONSOLE;
            break;
        }
    }
}

void Logger::resetConsole() const
{
    *m_os << RESET_CONSOLE << std::endl;
}

void Logger::printViewersCount() const
{
    int viewers = m_gameMgr->GetViewersCount();
    *m_os << "\t\t\t\t👁 " << viewers << std::endl;
}

void Logger::printLetters(bool line) const
{
    if (line)
    {
        *m_os << "\n    ⎪ A ⎪ B ⎪ C ⎪ D ⎪ E ⎪ F ⎪ G ⎪ H ⎪   \t";
        if (m_bWhiteTop) *m_os << m_gameMgr->GetDestroyedBlackPieces();
        else *m_os << m_gameMgr->GetDestroyedWhitePieces();
        *m_os << "\n ———————————————————————————————————————";
        printViewersCount();
    }
    else
    {
        *m_os << "    ⎪ A ⎪ B ⎪ C ⎪ D ⎪ E ⎪ F ⎪ G ⎪ H ⎪   \t";
        if (m_bWhiteTop) *m_os << m_gameMgr->GetDestroyedWhitePieces();
        else *m_os << m_gameMgr->GetDestroyedBlackPieces();
        *m_os << "\n" << std::endl;
    }
}

void Logger::printPieceChar(const Pieces::BasePiece* piece) const
{
    if (nullptr == piece)
    {
        *m_os << ' ';
        return;
    }
    *m_os << piece->GetPieceChar();
}

void Logger::printPieces(int lineIdx) const
{
    for (int i = 0; i < 8; ++i)
    {
        *m_os << " ";
        printPieceChar(m_board->GetBoard()[lineIdx][i]);
        *m_os << " |";
    }
}

void Logger::printLine(int lineIdx) const
{
    *m_os << "  " << lineIdx + 1 << " ⎪";
    printPieces(lineIdx);
    *m_os << " " << lineIdx + 1;
    *m_os << "\n ———————————————————————————————————————";
}

void Logger::printLastMove(int lineIdx) const
{
    Pieces::PrintableLastMove* pMove = m_gameMgr->GetLastMove(lineIdx);
    if ( nullptr == pMove )
    {
        return;
    }
    int oldX = pMove->oldPos.x + 1;
    char oldY = pMove->oldPos.y + 65;
    int newX = pMove->newPos.x + 1;
    char newY = pMove->newPos.y + 65;
    *m_os << "\t";
    *m_os << pMove->piece << " from " << oldY << oldX << " to " << newY << newX;
    *m_os << " | " << pMove->time;
}

void Logger::printLinesWT() const
{
    for (int i = 0; i < 8; ++i)
    {
        printLine(i);
        printLastMove(i);
        std::cout << std::endl;
    }
}

void Logger::printLinesBT() const
{
    for (int i = 7, j = 0; i >= 0; --i, ++j)
    {
        printLine(i);
        printLastMove(j);
        std::cout << std::endl;
    }
}

void Logger::printLines() const
{
    if (m_bWhiteTop)
    {
        printLinesWT();
    }
    else
    {
        printLinesBT();
    }
}

bool Logger::IsWhiteTop() const
{
    return m_bWhiteTop;
}

void Logger::ReverseBoard()
{
    m_bWhiteTop = !m_bWhiteTop;
}

void Logger::Print(const Utils::Exception& error) const
{
    Print(ERROR, "%s: %s", error.GetType(), error.GetMessage());
}

void Logger::PrintEndl() const
{
    Print(INFO, "");
}

void Logger::PrintHelp(const std::string& helpMsg) const
{
    std::cout << helpMsg;
}

void Logger::PrintBoard() const
{
    printLetters();
    printLines();
    printLetters(false);
    m_board->DestroyEmpties();
}

void Logger::SetStream(std::ostream* os)
{
    m_os = os;
}
