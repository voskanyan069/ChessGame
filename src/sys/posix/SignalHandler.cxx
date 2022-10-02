#include "utils/Exception.hxx"

#include <signal.h>

std::timed_mutex Sys::SignalHandler::m_signalsMutex;
std::map<int, std::function<void(int)> > Sys::SignalHandler::m_signalHandlers;

void Sys::SignalHandler::invokeCallback(int signal)
{
    std::unique_lock<std::timed_mutex> lock(m_signalsMutex, std::defer_lock);
    if (!lock.try_lock_for(std::chrono::seconds(1)))
    {
        return;
    }
    auto it = m_signalHandlers.find(signal);
    if (it != m_signalHandlers.end())
    {
        it->second(signal);
    }
}

void Sys::SignalHandler::registerHandler(int signal,
        const HandlerFunc& callback)
{
    m_signalHandlers.emplace(signal, callback);
}

void Sys::SignalHandler::AddSignalHandler(int signal,
        const HandlerFunc& callback)
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, signal);
    sa.sa_flags = 0;
    sa.sa_handler = Sys::SignalHandler::invokeCallback;
    sigaction(signal, &sa, 0);
    if (-1 == sigaction(signal, &sa, nullptr) && signal < __SIGRTMIN)
    {
        throw Utils::Exception("Failed to configure handler for signal: " +
                signal);
    }
    registerHandler(signal, callback);
}

void Sys::SignalHandler::SetCtrlCHandler(const HandlerFunc& callback)
{
    AddSignalHandler(SIGINT, callback);
}

void Sys::SignalHandler::DeleteSignalHandler(int sig)
{
    signal(sig, SIG_DFL);
}
