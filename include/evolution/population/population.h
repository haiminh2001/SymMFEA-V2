#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "individual.h"
#include "evolution/population/sub_population.h"
#include <vector>
class Population{
public:
    std::vector <Individual> individuals;
    std::vector <SubPopulation> sub_populations;
    Population(int num_tasks, int num_inviduals_per_tasks, DataPool* datapool);
};
#endif //SYMMFEA_POPULATION_H
