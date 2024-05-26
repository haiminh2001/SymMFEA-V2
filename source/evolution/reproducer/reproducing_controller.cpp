#include "evolution/reproducer/reproducing_controller.h"
#include <vector>

ReproducingController::ReproducingController(Population *population, std::vector<Mutation *> mutations, std::vector<Crossover *> crossovers)
    : population(population), mutations(mutations), crossovers(crossovers)
{

    auto num_subpopulations = population->sub_populations.size();
    auto num_operators = mutations.size() + crossovers.size();
    this->SMP = Eigen::Tensor<float, 3>(num_subpopulations, num_subpopulations, num_operators);
    this->SMP.setConstant(1.0);
}

void ReproducingController::_get_reproducing_context(SubPopulation **father_subpop, SubPopulation **mother_subpop, int *reproducing_operator_index)
{
    auto probs = this->SMP.data();
    std::vector<float> vec_probs = std::vector<float>(probs, probs + this->SMP.size());
    int reproduce_type = Random::random_choice<int>(vec_probs);

    int parent_subpop_index = reproduce_type % this->SMP.dimension(0);
    int mother_subpop_index = (reproduce_type / this->SMP.dimension(0)) % this->SMP.dimension(1);
    *reproducing_operator_index = reproduce_type / (this->SMP.dimension(0) * this->SMP.dimension(1));

    *father_subpop = this->population->sub_populations[parent_subpop_index];
    *mother_subpop = this->population->sub_populations[mother_subpop_index];
}

std::vector<IndividualPtr> ReproducingController::call()
{

    SubPopulation *father_subpop;
    SubPopulation *mother_subpop;
    int reproducing_operator_index;

    this->_get_reproducing_context(&father_subpop, &mother_subpop, &reproducing_operator_index);

    auto father = father_subpop->get_random();
    auto mother = mother_subpop->get_random();

    std::vector<IndividualPtr> offsprings;
    if (reproducing_operator_index < this->crossovers.size())
    {
        offsprings = this->crossovers[reproducing_operator_index]->call(father,
                                                                        mother,
                                                                        father_subpop->tree_spec);
    }
    else
    {
        auto mutation_operator_index = reproducing_operator_index - this->crossovers.size();
        auto mutation_offsprings_father = this->mutations[mutation_operator_index]->call(father, father_subpop->tree_spec);
        auto mutation_offsprings_mother = this->mutations[mutation_operator_index]->call(mother, mother_subpop->tree_spec);
        offsprings.insert(offsprings.end(), mutation_offsprings_father.begin(), mutation_offsprings_father.end());
        offsprings.insert(offsprings.end(), mutation_offsprings_mother.begin(), mutation_offsprings_mother.end());
    }

    return offsprings;
}