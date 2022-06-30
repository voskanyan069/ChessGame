#include "utils/Logger.hxx"
#include "chess/Board.hxx"
#include "pieces/BasePiece.hxx"

#include <iostream>

#define INFO_CONSOLE    "\033[32m"
#define WARN_CONSOLE    "\033[33m"
#define ERROR_CONSOLE   "\033[31m"
#define RESET_CONSOLE   "\033[0m"

Logger* Logger::GetInstance()
{
    static Logger* instance = new Logger();
    return instance;
}

Logger::Logger()
    : m_os(&std::cout)
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

void Logger::printLetters(bool line) const
{
    if (line)
    {
        *m_os << "\n    ⎪ A ⎪ B ⎪ C ⎪ D ⎪ E ⎪ F ⎪ G ⎪ H ⎪   " << std::endl;
        *m_os << " ———————————————————————————————————————" << std::endl;
    }
    else
    {
        *m_os << "    ⎪ A ⎪ B ⎪ C ⎪ D ⎪ E ⎪ F ⎪ G ⎪ H ⎪   \n" << std::endl;
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
        printPieceChar(Chess::Board::GetInstance()->GetBoard()[lineIdx][i]);
        *m_os << " |";
    }
}

void Logger::printLines() const
{
    for (int i = 0; i < 8; ++i)
    {
        *m_os << "  " << i + 1 << " ⎪";
        printPieces(i);
        *m_os << " " << i + 1;
        *m_os << "\n ———————————————————————————————————————" << std::endl;
    }
}

void Logger::SetStream(std::ostream* os)
{
    m_os = os;
}

void Logger::PrintBoard() const
{
    printLetters();
    printLines();
    printLetters(false);
}
