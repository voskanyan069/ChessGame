#ifndef __PIECES_EMPTY_PIECE_HXX__
#define __PIECES_EMPTY_PIECE_HXX__

#include "pieces/BasePiece.hxx"

namespace Pieces
{
    class EmptyPiece;
};

class Pieces::EmptyPiece : public Pieces::BasePiece
{
public:
    EmptyPiece(const Pieces::Position& position);
    ~EmptyPiece() = default;

protected:
    void getAvailableMoves(Pieces::Positions& positions) const override;
};

#endif // __PIECES_EMPTY_PIECE_HXX__

