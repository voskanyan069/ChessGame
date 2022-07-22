#ifndef __UTILS_EXCEPTION_HXX__
#define __UTILS_EXCEPTION_HXX__

#include <string>
#include <exception>

namespace Utils
{
    class Exception;
}

class Utils::Exception : public std::exception
{
public:
    Exception(const std::string& message="", const std::string& type="Error");
    ~Exception() = default;

public:
    std::string GetType() const;
    std::string GetMessage() const;
    char const* what() const throw();

private:
    const std::string m_type;
    const std::string m_message;
};

#endif // __UTILS_EXCEPTION_HXX__
