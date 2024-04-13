#include "central_units/individual_infos.h"

ArrayXXf IndividualInfos::objectives = ArrayXXf(1, 1);
ArrayXXf IndividualInfos::weight = ArrayXXf(1, 1);
ArrayXXf IndividualInfos::weightDelta = ArrayXXf(1, 1);
uint32_t IndividualInfos::num_objectives = 0;
void IndividualInfos::init(int max_num_individuals, int num_objectives, int max_length)
{
    IndividualInfos::num_objectives = (uint32_t)num_objectives;
    IndividualInfos::objectives = ArrayXXf((uint32_t)max_num_individuals + 1, IndividualInfos::num_objectives);
    IndividualInfos::weight = ArrayXXf::Random((uint32_t)max_num_individuals + 1, (uint32_t)max_length);
    IndividualInfos::weightDelta = ArrayXXf((uint32_t)max_num_individuals + 1, (uint32_t)max_length);
}
