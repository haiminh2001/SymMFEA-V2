#ifndef SYMMFEA_INDIVIDUAL_H
#define SYMMFEA_INDIVIDUAL_H
#include <vector>
#include "components/tree/tree.h"
#include "Eigen/Dense"

class Individual
{
public:
    int skill_factor;
    int64_t central_id;
    bool evaluated;
    Tree *genes;

    Individual(std::vector<Node *>, int skill_factor);
    Individual(int skill_factor, int max_index, int max_length, int max_depth);
    ~Individual();

    ArrayXf forward(const ArrayXXf &X, bool record_gradient = true) const;

    /// @brief
    /// Return the objectives of this individual
    /// First element is the main objective
    /// @return
    Eigen::ArrayXf objectives();

    void setObjective(float *objectives);

    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
};
#endif // SYMMFEA_INDIVIDUAL_H
