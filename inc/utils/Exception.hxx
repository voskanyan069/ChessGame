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
    Exception(const std::string& message="",
              const std::string& type="Error",
              int code=1);
    ~Exception() = default;

public:
    std::string GetType() const;
    std::string GetMessage() const;
    int GetErrorCode() const;
    char const* what() const throw();

private:
    const int m_code;
    const std::string m_type;
    const std::string m_message;
};

#endif // __UTILS_EXCEPTION_HXX__
