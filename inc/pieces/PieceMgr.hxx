#ifndef __PIECES_PIECE_MGR_HXX__
#define __PIECES_PIECE_MGR_HXX__

#include "pieces/BasePiece.hxx"
#include "utils/Exception.hxx"

#include <string>
#include <vector>
#include <iostream>

namespace Pieces
{
    inline void ConvertPosition(const std::string& str, Pieces::Position& pos)
    {
        if (2 == str.size() &&
            ((64 < (int)str[0] && 73 > (int)str[0]) ||
            (96 < (int)str[0] && 105 > (int)str[0])) &&
            (48 < (int)str[1] && 57 > (int)str[1]))
        {
            int reducer = 65;
            if (72 > (int)str[0])
            {
                reducer = 97;
            }
            int x = (int)str[0] - reducer;
            int y = (int)str[1] - 49;
            pos.x = x;
            pos.y = y;
            return;
        }
        throw Utils::Exception("Incorrect position");
    }

    template <typename T>
    inline T* CreatePiece(const Pieces::PieceColor& color,
            const Pieces::Position& position)
    {
        T* piece = new T(color, position);
        return piece;
    }
};

#endif // __PIECES_PIECE_MGR_HXX__
