#include "central_units/id_allocator.h"
#include "vector"
#include "iostream"

std::string OOM_WARING = "\nError: an individual can not be allocated";

// these are to create reference, the values do not matter
int64_t IdAllocator::OOM_POS = 0;
int64_t IdAllocator::cur_pos = 0;
uint64_t IdAllocator::num_allocated = 0;
int64_t IdAllocator::max_pos = 0;
std::mutex IdAllocator::lock;

std::vector<bool> IdAllocator::id_tracker(1);

void IdAllocator::init(uint64_t max_num_individuals)
{
    max_num_individuals++;
    IdAllocator::id_tracker = std::vector<bool>(max_num_individuals);
    IdAllocator::max_pos = max_num_individuals;
    IdAllocator::num_allocated = 0;
    IdAllocator::OOM_POS = 0;
    IdAllocator::cur_pos = 1;

}

int64_t IdAllocator::allocate()
{
    std::lock_guard<std::mutex> lock(IdAllocator::lock);
    auto start = IdAllocator::cur_pos;
    bool is_oom = false;
    if (IdAllocator::num_allocated == IdAllocator::max_pos)
        is_oom = true;

    while (IdAllocator::id_tracker[IdAllocator::cur_pos])
    {
        ++IdAllocator::cur_pos;
        if (IdAllocator::cur_pos == IdAllocator::max_pos)
            IdAllocator::cur_pos = IdAllocator::OOM_POS + 1;

        if (IdAllocator::cur_pos == start)
        {
            is_oom = true;
            break;
        }
    }

    if (is_oom)
    {
        std::cerr << OOM_WARING;
        throw std::bad_alloc();
    }

    IdAllocator::id_tracker[IdAllocator::cur_pos] = true;
    ++IdAllocator::num_allocated;

    return IdAllocator::cur_pos;
}

void IdAllocator::free(uint64_t index)
{
    std::lock_guard<std::mutex> lock(IdAllocator::lock);
    IdAllocator::id_tracker[index] = false;
    IdAllocator::num_allocated -= 1;
    IdAllocator::cur_pos = index;
    
}