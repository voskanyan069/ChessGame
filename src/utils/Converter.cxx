#include "utils/P2C_Converter.hxx"
#include "utils/C2P_Converter.hxx"

void P2C_Converter::ConvertPosition(const Proto::Position& src,
        Pieces::Position& dest)
{
    dest.x = src.x();
    dest.y = src.y();
}

void P2C_Converter::ConvertLastMoveInfo(const Proto::LastMoveInfo& src,
        Remote::LastMove& dest)
{
    P2C_Converter::ConvertPosition(src.oldposition(), dest.oldPos);
    P2C_Converter::ConvertPosition(src.newposition(), dest.newPos);
}

void C2P_Converter::ConvertPosition(const Pieces::Position& src,
        Proto::Position& dest)
{
    dest.set_x(src.x);
    dest.set_y(src.y);
}

void C2P_Converter::ConvertLastMoveInfo(const Remote::LastMove& src,
        Proto::LastMoveInfo& dest)
{
    C2P_Converter::ConvertPosition(src.oldPos, *(dest.mutable_oldposition()));
    C2P_Converter::ConvertPosition(src.newPos, *(dest.mutable_newposition()));
}
