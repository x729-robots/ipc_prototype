#include "leading.h"

int main(int argc, char* argv[])
{

    pthread_mutex_t* pmutex = NULL;
    pthread_mutexattr_t attrmutex;

    /* Initialise attribute to mutex. */
    pthread_mutexattr_init(&attrmutex);
    pthread_mutexattr_setpshared(&attrmutex,
                                 PTHREAD_PROCESS_SHARED); // используем базовую реализацию мьютекса, а не от std::, так как в std::mutex не
                                                          // поддерживается PTHREAD_PROCESS_SHARED, а это важно для моей мультисервисной архитектуры
    // TODO переделать на cactus_rt mutex, так как там всё это продумано

    pthread_cond_t* condition;
    pthread_mutex_t* mutex;
    char* message;
    int des_cond, des_msg, des_mutex;
    int mode = S_IRWXU | S_IRWXG;

    des_mutex = shm_open(leading_cv_mutex, O_CREAT | O_RDWR | O_TRUNC, mode);

    if (des_mutex < 0)
    {
        perror("can'open mutex from shm");
        exit(1);
    }

    if (ftruncate(des_mutex, sizeof(pthread_mutex_t)) == -1)
    {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        exit(-1);
    }

    mutex = (pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, des_mutex, 0);
    /* Initialise mutex. */

    if (mutex == MAP_FAILED)
    {
        perror("Error on mmap on mutex\n");
        exit(1);
    }

    pthread_mutex_init(pmutex, &attrmutex);

    pthread_cond_t* pcond = NULL;
    pthread_condattr_t attrcond;

    /* Initialise attribute to condition. */
    pthread_condattr_init(&attrcond);
    pthread_condattr_setpshared(&attrcond, PTHREAD_PROCESS_SHARED); // аналогично, std:: не поддерживает PTHREAD_PROCESS_SHARED, поэтому используем C
    // TODO найти в boost  PTHREAD_PROCESS_SHARED для condition variable

    des_cond = shm_open(leading_cv, O_CREAT | O_RDWR | O_TRUNC, mode);

    if (des_cond < 0)
    {
        perror("failure on shm_open on des_cond");
        exit(1);
    }

    if (ftruncate(des_cond, sizeof(pthread_cond_t)) == -1)
    {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        exit(-1);
    }

    condition = (pthread_cond_t*)mmap(NULL, sizeof(pthread_cond_t), PROT_READ | PROT_WRITE, MAP_SHARED, des_cond, 0);

    if (condition == MAP_FAILED)
    {
        perror("Error on mmap on condition\n");
        exit(1);
    }

    pthread_cond_init(pcond, &attrcond);

    // test leading signals to canapp thread
    for (int i; i < 5; i++)
    {
        sleep(1);

        pthread_mutex_lock(mutex);
        pthread_cond_signal(condition);
        printf("son signaled\n");
        pthread_mutex_unlock(mutex);
    }

    //TODO подумать, что где забыл, привести в более красивый вид

    // освобождаем ресурсы
    pthread_mutex_destroy(pmutex);
    pthread_mutexattr_destroy(&attrmutex);
    pthread_cond_destroy(pcond);
    pthread_condattr_destroy(&attrcond);
}