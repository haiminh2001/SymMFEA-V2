#ifndef SYMMFEA_INDIVIDUAL_H
#define SYMMFEA_INDIVIDUAL_H

#include "components/tree/tree.h"
#include "evolution/reproducer/tree_spec.h"

#include "Eigen/Dense"
#include <vector>
#include <memory>

class Individual
{
public:
    float father_fitness_score;
    float fitness_score;

    void set_fitness_score(float fitness_score);

    int skill_factor;
    int64_t central_id;
    Tree *genes;
    explicit Individual(int skill_factor);

    /**
     * @brief Constructs an Individual object.
     *
     * This constructor initializes an Individual from a pre-defined gene.
     * Used to create an individual from a reproducing procedure
     *
     * @param nodes A vector of Node pointers representing the genetic information of the individual.
     * @param skill_factor An integer representing the skill factor of the individual.
     * @param father_fitness_score The fitness value of the individual's father.
     */
    Individual(std::vector<Node *>, int skill_factor, float father_fitness_score);

    /**
     * @brief Constructs an Individual object.
     * This constructor is used to create a random individual with a tree specification.
     * Used to create an individual in the population intializing procedure.
     * @param skill_factor The skill factor of the individual.
     * @param tree_spec The TreeSpec object associated with the individual.

     */
    Individual(int skill_factor, TreeSpec *tree_spec);
    ~Individual();

    ArrayXf forward(const ArrayXXf &X, bool record_gradient = true) const;
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
};

typedef std::shared_ptr<Individual> IndividualPtr;
#endif // SYMMFEA_INDIVIDUAL_H
