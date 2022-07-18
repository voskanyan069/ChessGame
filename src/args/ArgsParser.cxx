#include "args/ArgsParser.hxx"

#include <sstream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

ArgsParser::ArgsParser(int argc, char** argv)
    : m_argc(argc)
    , m_argv(argv)
    , m_desc(new po::options_description("Allowed options"))
    , m_vm(new po::variables_map())
{
    m_desc->add_options()
        ("help,h", "show help message");
}

ArgsParser::~ArgsParser()
{
    delete m_desc;
    delete m_vm;
    CMDArguments::GetInstance()->ClearArguments();
}

template <typename T>
void ArgsParser::setOption(const std::string& key, const T& val)
{
    CMDArgument<T>* arg = new CMDArgument<T>(val);
    CMDArguments::GetInstance()->SetArgument(key, (ArgumentBase*)arg);
}

bool ArgsParser::ParseArguments()
{
    po::store(po::parse_command_line(m_argc, m_argv, *m_desc), *m_vm);
    po::notify(*m_vm);
    if (m_vm->count("help"))
    {
        return false;
    }
    for (const auto& it : *m_vm)
    {
        auto& value = it.second.value();
        if (auto v = boost::any_cast<int>(&value))
        {
            setOption(it.first, *v);
        }
        else if (auto v = boost::any_cast<std::string>(&value))
        {
            setOption(it.first, *v);
        }
    }
    return true;
}

void ArgsParser::GetHelpMessage(std::string& helpMsg)
{
    std::stringstream ss;
    ss << *m_desc;
    helpMsg = ss.str();
}
