#include "args/CMDArgument.hxx"
#include "args/ArgumentBase.hxx"
#include "utils/Exception.hxx"

CMDArguments::CMDArguments()
{
}

CMDArguments* CMDArguments::GetInstance()
{
	static CMDArguments* instance = new CMDArguments();
	return instance;
}

const ArgumentBase* CMDArguments::Find(const std::string& name) const
{
    const auto& it = m_arguments.find(name);
    if (it == m_arguments.end())
    {
        throw Utils::Exception(name + " not found");
    }
    return it->second;
}

void CMDArguments::SetArgument(const std::string& name, const bool value)
{
	CMDArgument<bool>* arg = new CMDArgument<bool>(value);
	SetArgument(name, (ArgumentBase*) arg);
}

void CMDArguments::SetArgument(const std::string& name, ArgumentBase* arg)
{
	m_arguments[name] = std::move(arg);
}

void CMDArguments::ClearArguments()
{
    for (const auto& arg : m_arguments)
    {
        delete arg.second;
    }
}
