#ifndef SYMMFEA_INDIVIDUAL_H
#define SYMMFEA_INDIVIDUAL_H
#include <vector>
#include "components/tree/tree.h"
#include "Eigen/Dense"

class Individual
{
public:
    int skill_factor;
    unsigned long central_id;
    bool evaluated;
    Tree *genes;

    Individual(std::vector<Node *>, int skill_factor);
    Individual(int skill_factor, int max_index, int max_length, int max_depth);
    ~Individual();

    ArrayXf eval(const ArrayXXf &X) const;

    Eigen::ArrayXf objectives();

    void setObjective(std::vector<float> objectives);

    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
};
#endif // SYMMFEA_INDIVIDUAL_H
