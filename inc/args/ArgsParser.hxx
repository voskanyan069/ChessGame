#ifndef __ARGS_ARGS_PARSER_HXX__
#define __ARGS_ARGS_PARSER_HXX__

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class ArgsParser
{
public:
    ArgsParser();
    ~ArgsParser();

public:
    void ParseArguments(int argc, char** argv);

private:
    void addOptions();
    void countOptions();

private:
    int m_argc;
    char** m_argv;
    po::variables_map* m_vm;
    po::options_description* m_desc;
};

#endif // __ARGS_ARGS_PARSER_HXX__
