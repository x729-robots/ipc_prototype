#include "leading.h"
#include <unistd.h>
#include "ccondvar.h"
#include "shm_names.h"
#include <iostream>

int main(int argc, char* argv[])
{
    ccondvar condvar(leading_cv,leading_cv_mutex);
    // test leading signals to canapp thread
    for (int i = 0; i < 3; i++)
    {
        condvar.signal2trailing();
        sleep(1);
    }

}