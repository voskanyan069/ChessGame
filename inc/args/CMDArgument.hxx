#ifndef __ARGS_CMD_ARGUMENT_HXX__
#define __ARGS_CMD_ARGUMENT_HXX__

#include <map>
#include <vector>
#include <string>

#include "args/ArgumentBase.hxx"

typedef std::map<std::string, ArgumentBase*> ArgsMap;

template <typename T>
class CMDArgument : ArgumentBase
{
public:
	CMDArgument(const T& rhs) : m_value(rhs)
    {
    }

public:
	const T& Get() const
    {
        return m_value;
    }

private:
	const T m_value;
};

class CMDArguments
{
public:
    static CMDArguments* GetInstance();
    CMDArguments(CMDArguments const&) = delete;
    void operator=(CMDArguments const&) = delete;

private:
    CMDArguments();

public:
	const ArgumentBase* Find(const std::string& name) const;
	void SetArgument(const std::string& name, const bool value);
	void SetArgument(const std::string& name, ArgumentBase* arg);
    void ClearArguments();

private:
	ArgsMap m_arguments;
};

typedef CMDArgument<int>         CMDIntArgument;
typedef CMDArgument<std::string> CMDStrArgument;

#endif // __ARGS_CMD_ARGUMENT_HXX__
