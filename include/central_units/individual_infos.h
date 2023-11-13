#ifndef SYMMFEA_INDIVIDUAL_INFOS_H
#define SYMMFEA_INDIVIDUAL_INFOS_H
#include "NumCpp.hpp"
class IndividualInfos
{
public:
    static nc::NdArray<float> objectives;
    static void init(int max_num_individuals, int num_objectives);
};



#endif // SYMMFEA_INDIVIDUAL_INFOS_H
