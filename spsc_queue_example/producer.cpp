#include <boost/lockfree/spsc_queue.hpp> // ring buffer

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

namespace bip = boost::interprocess;
namespace shm
{
    typedef bip::allocator<char, bip::managed_shared_memory::segment_manager> char_alloc;
    typedef bip::basic_string<char, std::char_traits<char>, char_alloc >      shared_string;

    typedef boost::lockfree::spsc_queue<
        shared_string, 
        boost::lockfree::capacity<10000> 
    > ring_buffer;
}

#include <unistd.h>

int main()
{
    // create segment and corresponding allocator
    bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 10000000);
    shm::char_alloc char_alloc(segment.get_segment_manager());

    // Ringbuffer fully constructed in shared memory. The element strings are
    // also allocated from the same shared memory segment. This vector can be
    // safely accessed from other processes.
    shm::ring_buffer *queue = segment.find_or_construct<shm::ring_buffer>("queue")();

    const char* messages[] = { "hello world", "the answer is 42", "where is your towel", 0 };
    int i (0);
    int counter(0);
    while(true)
    {
        for (const char** msg_it = messages; *msg_it; ++msg_it)
        {
            //sleep(1);
            std::cout << queue->push(shm::shared_string(*msg_it, char_alloc)) << "'\n";
            std::cout << "Processed: '" << i++ << "'\n";
            usleep(10);
        }
        //counter+=3;
        //if ( counter > 900000 )
        //{
        //    counter=0;
        //    usleep(20000000);
        //}
    }
}
