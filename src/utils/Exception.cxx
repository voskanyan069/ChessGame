#include "utils/Exception.hxx"

Utils::Exception::Exception(const std::string& message,
        const std::string& type,
        int code)
    : m_message(message)
    , m_type(type)
    , m_code(code)
{
}

std::string Utils::Exception::GetType() const
{
    return m_type;
}

std::string Utils::Exception::GetMessage() const
{
    return m_message;
}

int Utils::Exception::GetErrorCode() const
{
    return m_code;
}

char const* Utils::Exception::what() const throw()
{
    return m_message.c_str();
}
