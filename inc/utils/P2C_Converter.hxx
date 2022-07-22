#ifndef __UTILS_P2C_CONVERTER_HXX__
#define __UTILS_P2C_CONVERTER_HXX__

#include "utils/Types.hxx"
#include "protogen/ChessServerTypes.pb.h"

namespace P2C_Converter
{
    void ConvertPosition(const Proto::Position& src, Pieces::Position& dest);
    void ConvertLastMoveInfo(const Proto::LastMoveInfo& src,
            Remote::LastMove& dest);
}

#endif // __UTILS_P2C_CONVERTER_HXX__
