#include "evolution/selector.h"
#include "central_units/individual_infos.h"
#include "central_units/id_allocator.h"
#include "vector"

void Selector::call(SubPopulation *subpop, Eigen::Array<unsigned long, Eigen::Dynamic, 1> argpos)
{
    assert(subpop->individuals.size() == argpos.size());
    unsigned long num_orig = subpop->individuals.size();
    unsigned long num_keep = static_cast<unsigned long>(this->survive_ratio * num_orig);
    std::vector<Individual *> survivors;

    for (unsigned long index = 0; index < num_keep; ++index)
    {
        // discard invalid individuals
        if (subpop->individuals[argpos[index]]->central_id != 0)
            survivors.push_back(subpop->individuals[argpos[index]]);
    }

    for (unsigned long index = num_keep; index < subpop->individuals.size(); ++index)
    {
        delete subpop->individuals[argpos[index]];
    }

    assert(survivors.size() == num_keep);

    subpop->setIndividuals(survivors);
}

Selector::Selector(float survive_ratio)
{
    this->survive_ratio = survive_ratio;
}