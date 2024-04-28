#include "evolution/reproducer/variant.h"
std::vector<Individual*> Variant::call(Population *population)
{

    SubPopulation *father;
    SubPopulation *mother;

    population->get_random_subpopulations(&father, &mother);

    auto father_ind = father->get_random();
    auto mother_ind = mother->get_random();

    auto crossover_offsprings = this->crossover->call(father_ind, mother_ind);
    auto mutation_offsprings_father = this->mutation->call(father_ind);
    auto mutation_offsprings_mother = this->mutation->call(mother_ind);

    // Concatenate the offspring vectors
    std::vector<Individual*> offsprings;
    offsprings.insert(offsprings.end(), crossover_offsprings.begin(), crossover_offsprings.end());
    offsprings.insert(offsprings.end(), mutation_offsprings_father.begin(), mutation_offsprings_father.end());
    offsprings.insert(offsprings.end(), mutation_offsprings_mother.begin(), mutation_offsprings_mother.end());

    return offsprings;
}