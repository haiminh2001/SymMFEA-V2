#include "evolution/population/individual.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "components/tree/tree_handler.h"
#include <string>

Individual::Individual(int skill_factor)
    : skill_factor(skill_factor), evaluated(false), central_id(IdAllocator::allocate()) {}

Individual::Individual(std::vector<Node *> nodes, int skill_factor) : Individual(skill_factor)
{
    this->genes = new Tree(nodes, this->central_id);
}
Individual::Individual(int skill_factor, TreeSpec *tree_spec) : Individual(skill_factor)
{
    this->genes = new Tree(TreeHandler::create_tree(tree_spec), this->central_id);
}

ArrayXf Individual::forward(const ArrayXXf &X, bool record_gradient) const
{
    return this->genes->forward(X, record_gradient);
};

std::ostream &operator<<(std::ostream &os, const Individual &individual)
{
    os << *individual.genes;
    return os;
}

Individual::~Individual()
{
    IdAllocator::free(this->central_id);
    delete this->genes;
}