#include "evolution/algorithms/worker.h"

void Worker::run(GA *ga, Population *population)
{
    while (ga->quota->get_data() > 0)
    {
        int reproducing_operator_index;
        SubPopulation *father_subpop;
        SubPopulation *mother_subpop;
        ga->reproducing_controller->get_reproducing_context(&father_subpop, &mother_subpop, &reproducing_operator_index);
        auto offsprings = ga->reproducing_controller->call(father_subpop,
                                                           mother_subpop,
                                                           reproducing_operator_index);

        for (auto offspring : offsprings)
        {
            auto subpop = population->sub_populations[offspring->skill_factor];
            offspring.get()->set_fitness_score(ga->trainer->fit(offspring, subpop->dataview));

            if (ga->reproducing_controller->get_feedback(offspring,
                                                         father_subpop->skill_factor,
                                                         mother_subpop->skill_factor,
                                                         reproducing_operator_index))
            {
                subpop->insert_individual(offspring);
                subpop->remove_worst();
            }
        }

        (*ga->quota) -= offsprings.size();
        ga->progress_bar->update(offsprings.size(), population);
    }
}
