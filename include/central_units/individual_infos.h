#ifndef SYMMFEA_INDIVIDUAL_INFOS_H
#define SYMMFEA_INDIVIDUAL_INFOS_H
#include "Eigen/Dense"
using Eigen::ArrayXXf;

class IndividualInfos
{
public:
    // objectives are larger is better and the first column is the main objective
    static ArrayXXf objectives;
    static ArrayXXf weight;
    static ArrayXXf weightDelta;
    static void init(int max_num_individuals, int num_objectives, int max_length);
};



#endif // SYMMFEA_INDIVIDUAL_INFOS_H
