#include "evolution/algorithms/worker.h"
#include <iostream>

void Worker::run(GA *ga, Population *population)
{
    std::cout<<"Worker "<<this->id<<" is running\n";
    while (ga->quota->get_data() > 0)
    {
        auto offsprings = ga->reproducing_controller->call();

        for (auto offspring : offsprings)
        {
            auto subpop = population->sub_populations[offspring->skill_factor];
            auto metric = ga->trainer->fit(offspring, subpop->dataview);
            subpop->insert_individual(offspring, std::vector<float>({metric}));
            subpop->remove_worst();
        }
        
        (*ga->quota)-=offsprings.size();
        ga->progress_bar->update(offsprings.size(), population);
    }
}

