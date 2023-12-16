#include "evolution/population/individual.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "components/tree/tree_handler.h"

Individual::Individual(std::vector<Node *> nodes, int skill_factor)
{
    
    this->skill_factor = skill_factor;
    this->central_id = IdAllocator::allocate();
    this->genes = new Tree(nodes, this->central_id);
    this->evaluated = false;
}
Individual::Individual(int skill_factor, int max_index, int max_length, int max_depth)
{
    this->skill_factor = skill_factor;
    this->central_id = IdAllocator::allocate();
    this->evaluated = false;
    this->genes = create_tree(max_index, max_length, max_depth, this->central_id);
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

Eigen::ArrayXf Individual::objectives()
{
    return IndividualInfos::objectives(this->central_id, Eigen::all);
}

Individual::~Individual()
{
    IdAllocator::free(this->central_id);
}