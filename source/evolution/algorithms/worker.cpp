#include "evolution/algorithms/worker.h"

void Worker::run(GA *ga, Population *population)
{

    while (ga->quota->get_data() > 0)
    {
        auto offsprings = ga->variant->call(population);

        for (auto offspring : offsprings)
        {
            auto subpop = population->sub_populations[offspring->skill_factor];
            auto metric = ga->trainer->fit(offspring, subpop->dataview);
            std::vector<float> objectives = {metric};
            subpop->insert_individual(offspring, objectives);
        }
        (*ga->quota)-=offsprings.size();
    }
}

