#ifndef SYMMFEA_INDIVIDUAL_H
#define SYMMFEA_INDIVIDUAL_H
#include <vector>
#include "components/tree/tree.h"
class Individual{
public:
    int skill_factor;
    std::vector <float> objectives;
    Tree* genes;
    Individual(Tree* genes, int skill_factor);
    ArrayXf eval(const ArrayXXf& X) const;
};
#endif //SYMMFEA_INDIVIDUAL_H
