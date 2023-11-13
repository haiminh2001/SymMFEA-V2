#ifndef SYMMFEA_ID_ALLOCATOR_H
#define SYMMFEA_ID_ALLOCATOR_H
#include "NumCpp.hpp"
class IdAllocator
{
private:
    static nc::NdArray<bool> id_tracker;
    static unsigned long cur_pos;
    static unsigned long max_pos;
    static unsigned long num_allocated;

public:
    static void init(int max_num_individuals);
    static int allocate()
    {
        if (num_allocated == max_pos + 1)
            return -1;

        while (!id_tracker(id_tracker.rSlice(), cur_pos))
        {
            ++cur_pos;
            if (cur_pos == max_pos)
                cur_pos = 0;
        }

        id_tracker(id_tracker.rSlice(), cur_pos) = true;
        ++num_allocated;
        return cur_pos;
    }
    static void freeze(unsigned long index)
    {
        id_tracker(id_tracker.rSlice(), index) = false;
        num_allocated -= 1;
        cur_pos = index;
    }
};



#endif // SYMMFEA_ID_ALLOCATOR_H
