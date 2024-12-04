#pragma once
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

class ccondvar
{
  private:
    pthread_mutex_t* pmutex = NULL;
    pthread_mutexattr_t attrmutex;
    pthread_cond_t* pcond = NULL;
    pthread_condattr_t attrcond;
    std::string leading_cv;
    std::string leading_cv_mutex;

  public:
    ccondvar(std::string leading_cv, std::string leading_cv_mutex);
    //ccondvar(const std::string leading_cv, const std::string leading_cv_mutex);
    ~ccondvar();
    void signal2trailing();
    void leader_signalwait();
};