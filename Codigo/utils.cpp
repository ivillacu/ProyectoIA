#include "utils.hpp"

/*
 * @fn file_exist(const std::string)
 *
 * @brief
 *  Obtained from
 *  http://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
 * @param filename
 *  File name to check
 *
 * @return True if exist, else False
 */
bool file_exists(const std::string& filename)
{
    struct stat buffer;
    if (stat(filename.c_str(), &buffer) != -1)
    {
        return true;
    }
    return false;
}


/*
 * @fn check_options
 *
 * @param int argc
 *  Number of standard parameters
 * @param char* argv
 *  Parameters values
 *
 * @brief
 *   Checking the parameters of the program using the
 *   boost library.
 *
 * @return state of the parameters
 */
bool check_options(int argc, char *argv[], int &d1, int &d2, std::string &fname)
{
    float e = 0.0;
    po::options_description desc("Options");
    desc.add_options()
        ("help,h",   "Display message")
        ("input,i",  po::value<std::string>(), "Input data filename")
        ("d1,1",    po::value<int>(), "d1 parameter")
        ("d2,2",    po::value<int>(), "d2 parameter")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    /*
     * Help option
     */
    if (vm.count("help"))
    {
        std::cerr << desc << std::endl;
        return false;
    }

    /*
     * Input option
     */
    if (vm.count("input"))
    {
        fname = vm["input"].as<std::string>();

        if(!file_exists(fname))
        {
            std::cout << "Error: cannot access "
                      << fname
                      << ": No such file or directory"
                      << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: option requires an argument -- 'input'"
                  << std::endl;
        std::cerr << desc
                  << std::endl;
        return false;
    }

    /*
     * D1
     */
    if(vm.count("d1"))
    {
        d1 = vm["d1"].as<int>();
        d2 = vm["d2"].as<int>();
    }
    else
    {
        std::cerr << "Error: option requires an argument -- 'd1/d2'"
                  << std::endl;
        std::cerr << desc
                  << std::endl;
        return false;
    }


    return true;
}
