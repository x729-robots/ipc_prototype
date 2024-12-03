#include <cstdlib>
#include <iostream>

#include "help.h"
#include "cappargs.hpp"
#include "ccanopenmaster.h"

T_dummy_signals_dictionary_out dummy_signals_dictionary_out;
T_dummy_signals_dictionary_in dummy_signals_dictionary_in;

int main(int argc, char* argv[])
{
    CCANopenMaster canopen;
    std::cout << "canopen.testLibFun() == " << canopen.testLibFun() << std::endl;
    dummy_signals_dictionary_out[0].value = 5;
    canopen.testLibRealTimeTask(&dummy_signals_dictionary_out,
                                &dummy_signals_dictionary_in); // TODO move in in cactus_rt thread...
    int demo_value(0);
    while (canopen.event1_ring_buffer.pop(demo_value)) //вычерпываем события, которые нам поприходили
    {
        std::cout << "canopen.event1_ring_buffer.pop() == " << demo_value << std::endl; // thread safe and wait free... read queue of event 1
    }
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