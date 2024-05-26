#ifndef SYMMFEA_REPRODUCING_CONTROLLER_H
#define SYMMFEA_REPRODUCING_CONTROLLER_H
#include "evolution/population/individual.h"
#include "evolution/population/population.h"
#include "evolution/reproducer/mutation.h"
#include "evolution/reproducer/crossover.h"
#include "unsupported/Eigen/CXX11/Tensor"

class ReproducingController
{

private:
    /// @brief The subpopulation mating probability tensor
    /// @details The tensor is a 3D tensor with the dimensions being the number of subpopulations, the number of subpopulations, and the number of reproducing operators.
    Eigen::Tensor<float, 3> SMP;
    void _get_reproducing_context(SubPopulation **father_subpop, SubPopulation **mother_subpop, int* reproducing_operator_index);

    Population *population;
    std::vector<Mutation *> mutations;
    std::vector<Crossover *> crossovers;

public:
    ReproducingController(Population *population, std::vector<Mutation *> mutations, std::vector<Crossover *> crossovers);
    
    std::vector<std::shared_ptr<Individual>> call();
};
#endif // SYMMFEA_REPRODUCING_CONTROLLER_H
