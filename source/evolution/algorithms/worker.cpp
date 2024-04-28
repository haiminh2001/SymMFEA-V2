#include "evolution/algorithms/worker.h"

void Worker::do_one_task(){
    this->variation();
    this->evaluation();
    this->finish();
}