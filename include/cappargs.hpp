/**
 * @file cappargs.hpp
 * @author x729-robots (x729-robots@yandex.ru)
 * @brief Class for parse application command line arguments to instance of CAppArgs as const fields of this class
 * @version 0.1
 * @date 2024-11-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

class CAppArgs
{
  public:
    CAppArgs(int argc, char* argv[])
    try : argN(checkArgN(argc)), NetworkIniFileName(checkArg(argv[1])), CANopenMasterLibFileName(checkArg(argv[2]))
    {
        std::cout << "NetworkIniFileName=" << NetworkIniFileName << ", CANopenMasterLibFileName=" << CANopenMasterLibFileName << std::endl;
    }
    catch (...)
    {
    }

  private:
    int argN;

  public:
    const std::string NetworkIniFileName;
    const std::string CANopenMasterLibFileName;

  private:
    int checkArgN(int argc)
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
};
