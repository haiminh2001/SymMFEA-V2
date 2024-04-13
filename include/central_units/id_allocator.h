#ifndef SYMMFEA_ID_ALLOCATOR_H
#define SYMMFEA_ID_ALLOCATOR_H
#include "Eigen/Dense"

class IdAllocator
{
private:
    static std::vector<bool> id_tracker;

    static uint64_t cur_pos;
    static uint64_t max_pos;
    static uint64_t num_allocated;

public:
    // 0 position is reserved for OOM individuals
    static uint64_t OOM_POS;

    static void init(int max_num_individuals);
    static uint64_t allocate();
    static void free(uint64_t index);
};

#endif // SYMMFEA_ID_ALLOCATOR_H
