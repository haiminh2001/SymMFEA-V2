#include "evolution/population/individual.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"

Individual::Individual(Tree *genes, int skill_factor)
{
    this->genes = genes;
    this->skill_factor = skill_factor;
    this->central_id = IdAllocator::allocate();
    this->evaluated = false;
}

ArrayXf Individual::eval(const ArrayXXf &X) const
{
    return this->genes->eval(X);
};

std::ostream &operator<<(std::ostream &os, const Individual &individual)
{
    os << *individual.genes;
    return os;
}

void Individual::setObjective(std::vector<float> objectives)
{
    for (int i = 0; i < objectives.size(); ++i)
    {
        IndividualInfos::objectives(this->central_id, i) = objectives[i];
    }

    this->evaluated = true;
    
}