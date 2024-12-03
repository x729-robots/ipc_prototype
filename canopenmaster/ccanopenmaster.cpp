#include "ccanopenmaster.h"
#include <iostream> //TODO debug only
CCANopenMaster::CCANopenMaster() {}

int CCANopenMaster::testLibFun()
{
    return 1;
}

/**
 * @brief The canapp must call this function pereodically from real-time (SCHED-FIFO thread)
 *
 * @param test_value
 * @return int
 */
int CCANopenMaster::testLibRealTimeTask(T_dummy_signals_dictionary_out* dummy_signals_dictionary_out,
                                        T_dummy_signals_dictionary_in* dummy_signals_dictionary_in)
{
    // TODO cactus_rt::mutex_lock RTAI for whole function (requaerement of CANlib)
    int res(0);
    // TODO made processing of res in below functions
    res = process_and_send_data(dummy_signals_dictionary_out); // обрабатываем то, что нам понаприходило из CAN-интерфейса
    res = process_and_recive_data(dummy_signals_dictionary_in); // отсылаем всё, что накопилось в CAN-интерфейс
    const uint32_t MAX_EMULATE_EVENT1_N = 10;

    int test_echo_value = dummy_signals_dictionary_out->at(0).value; // zero element of dummy_signals_dictionary_out will be for demonstation
    for (uint32_t emulate_event1_n = 0; emulate_event1_n < MAX_EMULATE_EVENT1_N; emulate_event1_n++)
    {
        testLibCallBack1(test_echo_value++); // realy such function will call by different undefined conditions end events in CAN network
    }
    return 1;
}

/**
 * @brief Library will call such functions and we should handle events from this function in background thread as queue of nonrealyime  events
 *
 * @param test_value
 * @return int
 */
int CCANopenMaster::testLibCallBack1(int test_value)
{
    event1_ring_buffer.push(test_value);

    return 1;
}

T_dummy_signals_dictionary_in& CCANopenMaster::getDummy_signals_dictionary_in()
{
    // TODO cactus_rt RTAI lock
    T_dummy_signals_dictionary_in dummy_signals_dictionary_in_ = dummy_signals_dictionary_in;
    return dummy_signals_dictionary_in_;
}

void CCANopenMaster::setDummy_signals_dictionary_out(T_dummy_signals_dictionary_out dummy_signals_dictionary_out_)
{
    // TODO cactus_rt RTAI lock
    dummy_signals_dictionary_out = dummy_signals_dictionary_out_;
}

int CCANopenMaster::process_and_send_data(T_dummy_signals_dictionary_out* dummy_signals_dictionary_out)
{
    // call processing functions from CANlibrary
    return 1;
}

int CCANopenMaster::process_and_recive_data(T_dummy_signals_dictionary_in* dummy_signals_dictionary_in)
{
    // call processing functions from CANlibrary
    return 1;
}