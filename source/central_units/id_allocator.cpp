#include "central_units/id_allocator.h"
#include "vector"

Eigen::Array<bool, Eigen::Dynamic, 1> IdAllocator::id_tracker = Eigen::Array<bool, Eigen::Dynamic, 1>();
unsigned long IdAllocator::cur_pos = 0;
unsigned long IdAllocator::num_allocated = 0;
unsigned long IdAllocator::max_pos = 0;

void IdAllocator::init(int max_num_individuals)
{
    IdAllocator::id_tracker = Eigen::Array<bool, Eigen::Dynamic, 1>(max_num_individuals);
IdAllocator:
    max_pos = max_num_individuals;
}

int IdAllocator::allocate()
{
    auto start = cur_pos;
    if (num_allocated == max_pos + 1)
        return -1;

    while (id_tracker(cur_pos))
    {
        ++cur_pos;
        if (cur_pos == max_pos)
            cur_pos = 0;

        if (cur_pos == start)
            return -1;
    }

    id_tracker(cur_pos) = true;
    ++num_allocated;
    return cur_pos;
}

void IdAllocator::freeze(unsigned long index)
{
    id_tracker(index) = false;
    num_allocated -= 1;
    cur_pos = index;
}