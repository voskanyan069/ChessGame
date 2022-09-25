#ifndef __SYS_SIGNAL_HANDLER_HXX__
#define __SYS_SIGNAL_HANDLER_HXX__

#include <map>
#include <mutex>
#include <functional>

namespace Sys
{
    class SignalHandler;
}

class Sys::SignalHandler
{
public:
    typedef std::function<void(int)> HandlerFunc;

public:
    SignalHandler() = default;
    ~SignalHandler() = default;

public:
    static void AddSignalHandler(int signal, const HandlerFunc& callback);
    static void SetCtrlCHandler(const HandlerFunc& callback);
    static void DeleteSignalHandler(int signal);

private:
    static void registerHandler(int signal, const HandlerFunc& callback);
    static void invokeCallback(int signal);

private:
    static std::timed_mutex m_signalsMutex;
    static std::map<int, HandlerFunc> m_signalHandlers;
};

#endif // __SYS_SIGNAL_HANDLER_HXX__
