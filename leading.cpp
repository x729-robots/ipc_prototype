#include "leading.h"
#include <unistd.h>
#include "shm_names.h"
#include "ccondvar.h"

int main(int argc, char* argv[])
{
    ccondvar condvar(leading_cv,leading_cv_mutex);
    // test leading signals to canapp thread
    for (int i; i < 5; i++)
    {
        sleep(1);
    }

}