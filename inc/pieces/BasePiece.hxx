#ifndef __PIECES_BASE_PIECE_HXX__
#define __PIECES_BASE_PIECE_HXX__

#include "utils/Types.hxx"

#include <string>
#include <vector>

namespace Pieces
{
    class BasePiece;
    typedef std::vector<Position> Positions;
};

class Pieces::BasePiece
{
public:
    BasePiece(const std::string& name="Base", const PieceColor& color=UNDEF,
            const Position& position=Position(-1, -1));
    virtual ~BasePiece() = default;

public:
    void SetHittable(bool isHittable);
    bool IsHittable() const;
    const std::string& GetPieceName() const;
    const std::string& GetPieceChar() const;
    PieceColor GetColor() const;
    Position GetPosition() const;
    void Move(const Pieces::Position& position);
    void GetAvailableMoves(Pieces::Positions& positions);

protected:
    virtual void getAvailableMoves(Pieces::Positions& positions) const;
    void setPieceChar(const Pieces::PieceColor& color,
            const std::string& white, const std::string& black);

private:
    void resetPieceHittableStatus(const Pieces::Position& pos) const;
    bool comparePositions(const Pieces::Position& pos,
            const Pieces::Position& newPos) const;
    bool cleanPositionIfEnemy(const Pieces::Position& pos) const;
    void movePiece(const Pieces::Position& pos);
    bool findKingInPositions(const Pieces::Position& pKingPiece,
            const Pieces::Positions& positions) const;
    bool findKingInEnemyMoves(const Pieces::PieceColor& kingColor,
            const Pieces::PieceColor& enemyColor) const;
    bool isMyKingHittable(Pieces::BasePiece* pPiece) const;

protected:
    bool m_isHittable;
    std::string m_pieceName;
    std::string m_pieceChar;
    std::string m_pieceInitialChar;
    Pieces::PieceColor m_color;
    Pieces::Position m_position;
    Pieces::Positions m_vecAvailableMoves;
};

#endif // __PIECES_BASE_PIECE_HXX__
