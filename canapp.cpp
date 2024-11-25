#include <cstdlib>
#include <iostream>

#include "help.h"
#include "ccanopenmaster.h"
#include "cappargs.hpp"

int main(int argc, char* argv[])
{
    CCANopenMaster canopen; 
    canopen.test();
    try
    {
        CAppArgs AppArgs(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << ", can't create AppArgs(argc, argv)" << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}