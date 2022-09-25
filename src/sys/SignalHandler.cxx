#include "sys/SignalHandler.hxx"

#include <boost/system/api_config.hpp>

#ifdef BOOST_POSIX_API
#   include "./posix/SignalHandler.cxx"
#else
#   include "./ms/SignalHandler.cxx"
#endif
