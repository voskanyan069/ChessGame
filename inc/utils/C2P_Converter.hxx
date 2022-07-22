#ifndef __UTILS_C2P_CONVERTER_HXX__
#define __UTILS_C2P_CONVERTER_HXX__

#include "utils/Types.hxx"
#include "protogen/ChessServerTypes.pb.h"

namespace C2P_Converter
{
    void ConvertPosition(const Pieces::Position& src, Proto::Position& dest);
    void ConvertLastMoveInfo(const Remote::LastMove& src,
            Proto::LastMoveInfo& dest);
}

#endif // __UTILS_C2P_CONVERTER_HXX__
