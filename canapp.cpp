#include "help.h"
#include <cstdlib>
#include <iostream>

class CAppArgs
{
  public:
    CAppArgs(int argc, char* argv[])
    try : argN(checkArgN(argc)), NetworkIniFileName(checkArg(argv[1])), CANopenMasterLibFileName(checkArg(argv[2]))
    {
    }
    catch (...)
    {
    }

    const int checkArgN(int argc)
    {
        if (argc != 3)
        {
            std::cout << "Wrong arguments number..." << std::endl; // TODO add
            std::cout << help_message() << std::endl;
            throw std::exception(); // TODO made exeption handler
        }
        return argc;
    }
    const std::string checkArg(char* arg)
    {
        if (arg == NULL)
        {
            throw std::exception(); // TODO made exeption handler
        }
        return std::string(arg); // TODO check argv[x] to correctness
    }

    const int argN;
    const std::string NetworkIniFileName;
    const std::string CANopenMasterLibFileName;
};

int main(int argc, char* argv[])
{
    try
    {
        CAppArgs AppArgs(argc, argv);
        std::cout << "AppArgs.NetworkIniFileName=" << AppArgs.NetworkIniFileName
                  << ", AppArgs.CANopenMasterLibFileName=" << AppArgs.CANopenMasterLibFileName << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << ", can't create AppArgs(argc, argv)" << '\n';
    }
    return EXIT_SUCCESS;
}