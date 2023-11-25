#ifndef SYMMFEA_INDIVIDUAL_INFOS_H
#define SYMMFEA_INDIVIDUAL_INFOS_H
#include "Eigen/Dense"
using Eigen::ArrayXXf;

class IndividualInfos
{
public:
    // objectives are larger is better
    static ArrayXXf objectives;
    static void init(int max_num_individuals, int num_objectives);
};



#endif // SYMMFEA_INDIVIDUAL_INFOS_H
