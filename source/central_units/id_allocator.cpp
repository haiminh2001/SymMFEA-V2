#include "central_units/id_allocator.h"
#include "vector"
#include "iostream"


unsigned long IdAllocator::OOM_POS = 0;
unsigned long IdAllocator::cur_pos = IdAllocator::OOM_POS + 1;
unsigned long IdAllocator::num_allocated = 0;
unsigned long IdAllocator::max_pos = 0;

std::vector<bool> IdAllocator::id_tracker (1);

void IdAllocator::init(int max_num_individuals)
{
    max_num_individuals++;
    IdAllocator::id_tracker = std::vector<bool> (max_num_individuals);
    IdAllocator::max_pos = max_num_individuals;
    IdAllocator::num_allocated = 0;

}

unsigned long IdAllocator::allocate()
{
    auto start = IdAllocator::cur_pos;
    if (IdAllocator::num_allocated == IdAllocator::max_pos + 1)
        
        return IdAllocator::OOM_POS;

    while (IdAllocator::id_tracker[IdAllocator::cur_pos])
    {
        ++IdAllocator::cur_pos;
        if (IdAllocator::cur_pos == IdAllocator::max_pos)
            IdAllocator::cur_pos = IdAllocator::OOM_POS + 1;

        if (IdAllocator::cur_pos == start)
            return IdAllocator::OOM_POS;
    }

    IdAllocator::id_tracker[IdAllocator::cur_pos] = true;
    ++IdAllocator::num_allocated;
    return IdAllocator::cur_pos;
}

void IdAllocator::free(unsigned long index)
{
    IdAllocator::id_tracker[index] = false;
    IdAllocator::num_allocated -= 1;
    IdAllocator::cur_pos = index;
}