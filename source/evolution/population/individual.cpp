#include "evolution/population/individual.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "components/tree/tree_handler.h"

#include <limits>
#include <string>

Individual::Individual(int skill_factor)
    : skill_factor(skill_factor), central_id(IdAllocator::allocate()) {}

Individual::Individual(std::vector<Node *> nodes, int skill_factor, float father_fitness_score) : Individual(skill_factor)
{
    this->genes = new Tree(nodes, this->central_id);
    this->father_fitness_score = father_fitness_score;
}
Individual::Individual(int skill_factor, TreeSpec *tree_spec) : Individual(skill_factor)
{
    this->genes = new Tree(TreeHandler::create_tree(tree_spec), this->central_id);
    this->set_fitness_score(-std::numeric_limits<float>::max());
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

void Individual::set_fitness_score(float fitness_score)
{
    this->fitness_score = fitness_score;
}