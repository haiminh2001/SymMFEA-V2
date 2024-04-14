#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "vector"
#include "iostream"


int64_t IdAllocator::OOM_POS = 0;
int64_t IdAllocator::cur_pos = IdAllocator::OOM_POS + 1;
uint64_t IdAllocator::num_allocated = 0;
int64_t IdAllocator::max_pos = 0;

std::vector<bool> IdAllocator::id_tracker (1);

void IdAllocator::init(int max_num_individuals)
{
    max_num_individuals++;
    IdAllocator::id_tracker = std::vector<bool> (max_num_individuals);
    IdAllocator::max_pos = max_num_individuals;
    IdAllocator::num_allocated = 0;

}

int64_t IdAllocator::allocate()
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

void IdAllocator::free(uint64_t index)
{
    IdAllocator::id_tracker[index] = false;
    IdAllocator::num_allocated -= 1;
    IdAllocator::cur_pos = index;
    IndividualInfos::weight.row(index).setOnes();
}