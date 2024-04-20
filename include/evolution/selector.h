#ifndef SYMMFEA_SELECTOR_H
#define SYMMFEA_SELECTOR_H

#include "evolution/population/sub_population.h"
#include "Eigen/Dense"

class Selector
{
private:
    uint32_t initial_population_size;
    uint32_t final_population_size;
    uint32_t num_generations;
    uint32_t calculate_num_survive(uint32_t current_generation);

public:
    void call(SubPopulation *subpop, Eigen::Array<uint64_t, Eigen::Dynamic, 1> argpos, uint32_t current_generation);
    Selector(uint32_t initial_population_size, uint32_t final_population_size, uint32_t num_generations)
        : initial_population_size(initial_population_size),
          final_population_size(final_population_size),
          num_generations(num_generations){};
};

#endif // SYMMFEA_SELECTOR_H
