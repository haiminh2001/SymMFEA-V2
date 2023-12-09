#include "central_units/individual_infos.h"

ArrayXXf IndividualInfos::objectives = ArrayXXf::Random(1, 1);

void IndividualInfos::init(int max_num_individuals, int num_objectives)
{
    IndividualInfos::objectives = ArrayXXf::Random((unsigned int)max_num_individuals + 1, (unsigned int)num_objectives);
}
