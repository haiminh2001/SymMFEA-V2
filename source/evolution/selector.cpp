#include "evolution/selector.h"
#include "central_units/individual_infos.h"
#include "vector"

void Selector::call(SubPopulation &subpop, Eigen::Array<unsigned long, Eigen::Dynamic, 1> argpos)
{
    unsigned long num_orig = subpop.individuals.size();
    unsigned long num_keep = static_cast<unsigned long>(this->survive_ratio * num_orig);
    std::vector<Individual> survivor;

    for (unsigned long index = 0; index < num_keep; ++index)
    {
        survivor.push_back(subpop.individuals[argpos[index]]);
    }
    assert(survivor.size() == num_keep);

    subpop.individuals = survivor;
}

Selector::Selector(float survive_ratio)
{
    this->survive_ratio = survive_ratio;
}