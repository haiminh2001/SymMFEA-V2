#include "central_units/individual_infos.h"

nc::NdArray<float> IndividualInfos::objectives = nc::empty<float>(1, 1);

void IndividualInfos::init(int max_num_individuals, int num_objectives)
{
    IndividualInfos::objectives = nc::empty<float>({(unsigned int)max_num_individuals, (unsigned int)num_objectives});
}
