#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <sys/stat.h>

namespace po = boost::program_options;
bool file_exists(const std::string&);
bool check_options(int argc, char *argv[], int&, int&, std::string&);
