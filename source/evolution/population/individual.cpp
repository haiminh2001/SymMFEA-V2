#include "evolution/population/individual.h"
#include "central_units/id_allocator.h"

Individual::Individual(Tree* genes, int skill_factor){
    this->genes = genes;
    this->skill_factor = skill_factor;
    this->central_id = IdAllocator::allocate();
}

ArrayXf Individual::eval(const ArrayXXf& X) const{
    return this->genes->eval(X);
};

std::ostream &operator<<(std::ostream &os, const Individual &individual)
{
    os<<*individual.genes;
    return os;
}
