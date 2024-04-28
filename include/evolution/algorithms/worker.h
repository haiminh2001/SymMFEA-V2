#ifndef SYMMFEA_WORKER_H
#define SYMMFEA_WORKER_H
#include "evolution/population/population.h"
class Worker
{
private:
    void variation();
    void evaluation();
    void finish();
    void do_one_task();
public:
    Worker();
    void run(Population *population);
    
};
#endif // SYMMFEA_WORKER_H
