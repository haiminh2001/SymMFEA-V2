#include "central_units/individual_infos.h"

ArrayXXf IndividualInfos::objectives = ArrayXXf(1, 1);
ArrayXXf IndividualInfos::weight = ArrayXXf(1, 1);
ArrayXXf IndividualInfos::weightDelta = ArrayXXf(1, 1);

void IndividualInfos::init(int max_num_individuals, int num_objectives, int max_length)
{
    IndividualInfos::objectives = ArrayXXf((unsigned int)max_num_individuals + 1, (unsigned int)num_objectives);
    IndividualInfos::weight = ArrayXXf::Random((unsigned int)max_num_individuals + 1, (unsigned int)max_length);
    IndividualInfos::weightDelta = ArrayXXf((unsigned int)max_num_individuals + 1, (unsigned int)max_length);
}
