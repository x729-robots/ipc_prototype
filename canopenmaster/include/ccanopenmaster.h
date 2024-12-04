/**
 * @brief CANopen master C-library wrapper C++ class
 *
 */
#pragma once
#include <array>
#include <boost/lockfree/spsc_queue.hpp> // ring buffer

typedef int event1;
const uint32_t MAX_EVENT1_QUEUE_SIZE(1000);
typedef boost::lockfree::spsc_queue<event1, boost::lockfree::capacity<MAX_EVENT1_QUEUE_SIZE>> T_event1_ring_buffer;
struct S_signal
{
    uint64_t value;
    uint64_t time;
    uint64_t status;
};

// TODO в реальности всё это будет не статически в коде, а конфигурируемым через ini или xml
const std::size_t DUMMY_SIGNALS_DICT_SIZE_IN(+1005); // тестовый размер сигналов от блоконтактов и датчиков по CAN
const std::size_t DUMMY_SIGNALS_DICT_SIZE_OUT(+1005); // тестовый размер сигналов управления контакторами и прочим оборудованием
typedef std::array<S_signal, DUMMY_SIGNALS_DICT_SIZE_IN> T_dummy_signals_dictionary_in;
typedef std::array<S_signal, DUMMY_SIGNALS_DICT_SIZE_OUT> T_dummy_signals_dictionary_out;
//TODO made cactus_rt RTAI mutex for DUMMY_SIGNALS_DICT_SIZE_IN
//TODO made cactus_rt RTAI mutex for DUMMY_SIGNALS_DICT_SIZE_OUT

class CCANopenMaster
{
  public:
    CCANopenMaster();
    int testLibFun();
    int testLibCallBack1(int test_value);
    int testLibRealTimeTask(T_dummy_signals_dictionary_out* dummy_signals_dictionary_out,
                            T_dummy_signals_dictionary_in* dummy_signals_dictionary_in);

    T_event1_ring_buffer event1_ring_buffer;

    T_dummy_signals_dictionary_in& getDummy_signals_dictionary_in();

    void setDummy_signals_dictionary_out(T_dummy_signals_dictionary_out dummy_signals_dictionary_out_);

  private:
    T_dummy_signals_dictionary_in dummy_signals_dictionary_in;
    T_dummy_signals_dictionary_out dummy_signals_dictionary_out;
    int process_and_send_data(T_dummy_signals_dictionary_in* dummy_signals_dictionary_in);
    int process_and_recive_data(T_dummy_signals_dictionary_out* dummy_signals_dictionary_out);

    //TODO think about destructors, optimizations and move semantics after...
};