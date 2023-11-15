#ifndef SYMMFEA_ID_ALLOCATOR_H
#define SYMMFEA_ID_ALLOCATOR_H
#include "Eigen/Dense"

class IdAllocator
{
private:
    static Eigen::Array<bool, Eigen::Dynamic, 1>  id_tracker;
    static unsigned long cur_pos;
    static unsigned long max_pos;
    static unsigned long num_allocated;

public:
    static void init(int max_num_individuals);
    static int allocate();
    static void freeze(unsigned long index);
};



#endif // SYMMFEA_ID_ALLOCATOR_H
