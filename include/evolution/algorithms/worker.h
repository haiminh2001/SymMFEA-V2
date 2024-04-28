#ifndef SYMMFEA_WORKER_H
#define SYMMFEA_WORKER_H
#include "evolution/population/population.h"
#include "evolution/algorithms/GA.h"

class Worker
{
private:
    int64_t variation(GA* ga, Population *population);

public:
    void run(GA* ga, Population *population);
};
#endif // SYMMFEA_WORKER_H
