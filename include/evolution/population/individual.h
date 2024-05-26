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
    int skill_factor;
    int64_t central_id;
    bool evaluated;
    Tree *genes;
    explicit Individual(int skill_factor);
    Individual(std::vector<Node *>, int skill_factor);
    Individual(int skill_factor, TreeSpec *tree_spec);
    ~Individual();

    ArrayXf forward(const ArrayXXf &X, bool record_gradient = true) const;
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
};

typedef std::shared_ptr<Individual> IndividualPtr;
#endif // SYMMFEA_INDIVIDUAL_H
