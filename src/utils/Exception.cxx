#include "utils/Exception.hxx"

Utils::Exception::Exception(const std::string& message)
    : m_message(message)
{
}

std::string Utils::Exception::GetMessage()
{
    return m_message;
}

char const* Utils::Exception::what() const throw()
{
    return m_message.c_str();
}
