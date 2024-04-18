#include "evolution/reproducer/variant.h"
void Variant::call(Population* population)
{
    auto crossover_offsprings = this->crossover->call(population);
    auto mutation_offsprings = this->mutation->call(population);    

    population->append(crossover_offsprings);
    population->append(mutation_offsprings);   
}