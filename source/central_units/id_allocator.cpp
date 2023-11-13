#include "central_units/id_allocator.h"
#include "vector"

nc::NdArray<bool> IdAllocator::id_tracker = nc::empty<bool>(1, 1);
unsigned long IdAllocator::cur_pos = 0;
unsigned long IdAllocator::num_allocated = 0;
unsigned long IdAllocator::max_pos = 0;

void IdAllocator::init(int max_num_individuals)
{
    IdAllocator::id_tracker = nc::zeros<bool>(1, (unsigned int)max_num_individuals);
    IdAllocator:max_pos = max_num_individuals;
}
