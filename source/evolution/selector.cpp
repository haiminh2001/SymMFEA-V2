#include "evolution/selector.h"
#include "central_units/individual_infos.h"
#include "central_units/id_allocator.h"
#include "vector"

void Selector::call(SubPopulation *subpop, Eigen::Array<uint64_t, Eigen::Dynamic, 1> argpos, uint32_t current_generation)
{
    assert(subpop->individuals.size() == argpos.size());

    uint32_t num_keep = this->calculate_num_survive(current_generation);

    // prevent the subpop from being evaporated
    if (num_keep < 1)
        num_keep = 1;

    std::vector<Individual *> survivors;

    uint32_t num_discarded = 0;

    for (uint32_t index = 0; index < num_keep; ++index)
    {
        // discard invalid individuals
        if (subpop->individuals[argpos[index]]->central_id != 0)
            survivors.push_back(subpop->individuals[argpos[index]]);
        else
            num_discarded += 1;
    }

    for (uint32_t index = num_keep; index < subpop->individuals.size(); ++index)
    {
        // return the central_id to the coordinator
        delete subpop->individuals[argpos[index]];
    }

    assert(survivors.size() == num_keep - num_discarded);

    subpop->setIndividuals(survivors);
}

uint32_t Selector::calculate_num_survive(uint32_t current_generation)
{
    double ratio = static_cast<double>(current_generation) / this->num_generations;
    return this->initial_population_size - static_cast<uint32_t>((this->initial_population_size - this->final_population_size) * ratio);
}