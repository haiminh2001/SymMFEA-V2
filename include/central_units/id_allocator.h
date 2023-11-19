#ifndef SYMMFEA_ID_ALLOCATOR_H
#define SYMMFEA_ID_ALLOCATOR_H
#include "Eigen/Dense"

class IdAllocator
{
private:
    static Eigen::Array<bool, Eigen::Dynamic, 1>  id_tracker;
    

    //0 position is reserved for OOM individuals
    static unsigned long OOM_POS;
    static unsigned long cur_pos;
    static unsigned long max_pos;
    static unsigned long num_allocated;

public:
    static void init(int max_num_individuals);
    static unsigned long allocate();
    static void freeze(unsigned long index);
};



#endif // SYMMFEA_ID_ALLOCATOR_H
