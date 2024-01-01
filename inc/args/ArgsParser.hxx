#ifndef __ARGS_ARGS_PARSER_HXX__
#define __ARGS_ARGS_PARSER_HXX__

#include "args/CMDArgument.hxx"

#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class ArgsParser
{
public:
    ArgsParser(int argc, char** argv);
    ~ArgsParser();

public:
    void ParseArguments();
    void GetHelpMessage(std::string& helpMsg);

public:
    void AddSwitch(const char* key, const char* desc, bool& value)
    {
        m_desc->add_options()
            (key, po::bool_switch(&value), desc);
    }

    template <typename T>
    void AddOption(const char* key, const char* desc, const T& defaultValue)
    {
        m_desc->add_options()
            (key, po::value<T>()->default_value(defaultValue), desc);
    }

private:
    template <typename T>
    void setOption(const std::string& key, const T& val);

private:
    int m_argc;
    char** m_argv;
    po::variables_map* m_vm;
    po::options_description* m_desc;
};

#endif // __ARGS_ARGS_PARSER_HXX__
