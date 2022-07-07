#ifndef __PIECES_PIECE_MGR_HXX__
#define __PIECES_PIECE_MGR_HXX__

#include "pieces/BasePiece.hxx"
#include "utils/Exception.hxx"

#include <string>

namespace Pieces
{
    inline void ConvertPosition(const std::string& str, Pieces::Position& pos)
    {
        if (2 == str.size() &&
            ((64 < (int)str[0] && 73 > (int)str[0]) ||
            (96 < (int)str[0] && 105 > (int)str[0])) &&
            (48 < (int)str[1] && 57 > (int)str[1]))
        {
            int reducer = 97;
            if (72 > (int)str[0])
            {
                reducer = 65;
            }
            pos.x = (int)str[1] - 49;
            pos.y = (int)str[0] - reducer;
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
