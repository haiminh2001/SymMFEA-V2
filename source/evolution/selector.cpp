#include "evolution/selector.h"
#include "central_units/individual_infos.h"
#include "central_units/id_allocator.h"
#include "vector"

void Selector::call(SubPopulation *subpop, Eigen::Array<uint64_t, Eigen::Dynamic, 1> argpos)
{
    assert(subpop->individuals.size() == argpos.size());
    uint64_t num_orig = subpop->individuals.size();
    uint64_t num_keep = static_cast<uint64_t>(this->survive_ratio * num_orig);
    
    // prevent the subpop from being evaporated
    if (num_keep <= 0) num_keep = 1;

    std::vector<Individual *> survivors;

    uint64_t num_discarded = 0;

    for (uint64_t index = 0; index < num_keep; ++index)
    {
        // discard invalid individuals
        if (subpop->individuals[argpos[index]]->central_id != 0)
            survivors.push_back(subpop->individuals[argpos[index]]);
        else num_discarded += 1;
    }

    for (uint64_t index = num_keep; index < subpop->individuals.size(); ++index)
    {
        // return the central_id to the coordinator
        delete subpop->individuals[argpos[index]];
    }

    assert(survivors.size() == num_keep - num_discarded);

    subpop->setIndividuals(survivors);
}

Selector::Selector(float survive_ratio)
{
    this->survive_ratio = survive_ratio;
}