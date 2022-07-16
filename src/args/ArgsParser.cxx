#include "args/ArgsParser.hxx"
#include "args/CMDArgument.hxx"
#include "utils/Logger.hxx"

#include <sstream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

ArgsParser::ArgsParser()
    : m_argc(0)
    , m_argv(nullptr)
    , m_desc(new po::options_description("Allowed options"))
    , m_vm(new po::variables_map())
{
}

ArgsParser::~ArgsParser()
{
    delete m_argv;
    delete m_desc;
    delete m_vm;
    CMDArguments::GetInstance()->ClearArguments();
}

void ArgsParser::ParseArguments(int argc, char** argv)
{
    m_argc = argc;
    m_argv = argv;
    addOptions();
    if (m_vm->count("help"))
    {
        std::stringstream ss;
        ss << *m_desc;
        Logger::GetInstance()->PrintHelp(ss.str());
        std::exit(1);
    }
    countOptions();
}

void ArgsParser::countOptions()
{
    CMDStrArgument* arg = nullptr;

    // Address of host
    arg = new CMDStrArgument((*m_vm)["host"].as<std::string>());
    CMDArguments::GetInstance()->SetArgument("host", (ArgumentBase*)arg);
}

void ArgsParser::addOptions()
{
    m_desc->add_options()
        ("help,h", "show help message")
        ("host,H", po::value<std::string>()->default_value("localhost"),
         "host address to connect")
        ;
    po::store(po::parse_command_line(m_argc, m_argv, *m_desc), *m_vm);
    po::notify(*m_vm);
}
