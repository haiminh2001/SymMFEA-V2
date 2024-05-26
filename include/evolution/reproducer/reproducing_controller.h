#ifndef SYMMFEA_REPRODUCING_CONTROLLER_H
#define SYMMFEA_REPRODUCING_CONTROLLER_H
#include "evolution/population/individual.h"
#include "evolution/population/population.h"
#include "evolution/reproducer/mutation.h"
#include "evolution/reproducer/crossover.h"
#include "unsupported/Eigen/CXX11/Tensor"

#include <mutex>
/**
 * @class ReproducingController
 * @brief Class responsible for controlling the reproduction process in a population.
 *
 * The ReproducingController class manages the reproduction process in a population.
 * It contains the subpopulation mating probability tensor, the population, and the list of mutations and crossovers.
 * It provides methods to perform the reproduction process and retrieve feedback for the offspring.
 */
class ReproducingController
{
private:
    std::recursive_mutex lock; ///< Mutex to lock the update process
    Eigen::Tensor<float, 3> SMP; ///< The subpopulation mating probability tensor

    Population *population;              ///< Pointer to the population
    std::vector<Mutation *> mutations;   ///< List of mutation operators
    std::vector<Crossover *> crossovers; ///< List of crossover operators

public:
    /**
     * @brief Retrieves the reproducing context.
     *
     * This function retrieves the reproducing context, which includes the father subpopulation,
     * the mother subpopulation, and the index of the reproducing operator to be used.
     *
     * @param father_subpop Pointer to store the father subpopulation.
     * @param mother_subpop Pointer to store the mother subpopulation.
     * @param reproducing_operator_index Pointer to store the index of the reproducing operator.
     */
    void get_reproducing_context(SubPopulation **father_subpop, SubPopulation **mother_subpop, int *reproducing_operator_index);

    /**
     * @brief Constructs a ReproducingController object.
     * @param population Pointer to the population.
     * @param mutations List of mutation operators.
     * @param crossovers List of crossover operators.
     */
    ReproducingController(Population *population, std::vector<Mutation *> mutations, std::vector<Crossover *> crossovers);

    /**
     * @brief Performs the reproduction process.
     * @param father_subpop Pointer to the father subpopulation.
     * @param mother_subpop Pointer to the mother subpopulation.
     * @param reproducing_operator_index Pointer to the index of the reproducing operator to be used.
     * @return Vector of offspring individuals.
     */
    std::vector<IndividualPtr> call(SubPopulation *father_subpop,
                                    SubPopulation *mother_subpop,
                                    int reproducing_operator_index);

    /**
     * @brief Retrieves feedback for the given offspring.
     *
     * This function is responsible for obtaining feedback for the specified offspring.
     * The feedback is used to evaluate the efficiency of the reproducing procedure.
     *
     * @param offspring Pointer to the offspring for which feedback is to be obtained.
     * @param father_subpop_index Index of the father subpopulation.
     * @param mother_subpop_index Index of the mother subpopulation.
     * @param reproducing_operator_index Index of the reproducing operator used for the offspring.
     */
    void get_feedback(IndividualPtr offspring,
                      int father_subpop_index,
                      int mother_subpop_index,
                      int reproducing_operator_index);
};
#endif // SYMMFEA_REPRODUCING_CONTROLLER_H
