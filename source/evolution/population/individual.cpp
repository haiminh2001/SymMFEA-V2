#include "evolution/population/individual.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "components/tree/tree_handler.h"
#include <iostream>
#include <string>
std::string OOM_WARING = "Warning: an individual can not bet allocated";

Individual::Individual(std::vector<Node *> nodes, int skill_factor)
{

    this->skill_factor = skill_factor;
    this->central_id = IdAllocator::allocate();

    if (this->central_id == IdAllocator::OOM_POS)
        std::cerr << OOM_WARING;

    this->genes = new Tree(nodes, this->central_id);
    this->evaluated = false;
}
Individual::Individual(int skill_factor, int max_index, int max_length, int max_depth)
{
    this->skill_factor = skill_factor;
    this->central_id = IdAllocator::allocate();

    if (this->central_id == IdAllocator::OOM_POS)
        std::cerr << OOM_WARING;
    this->evaluated = false;
    this->genes = create_tree(max_index, max_length, max_depth, this->central_id);
}

ArrayXf Individual::forward(const ArrayXXf &X) const
{
    return this->genes->forward(X);
};

std::ostream &operator<<(std::ostream &os, const Individual &individual)
{
    os << *individual.genes;
    return os;
}

/// @brief
/// set the individual objectives and set the "evaluated" attribute to "true"
/// @param objectives
void Individual::setObjective(float *objectives)
{
    for (int i = 0; i < IndividualInfos::num_objectives; ++i)
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