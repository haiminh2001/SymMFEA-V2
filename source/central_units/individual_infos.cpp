#include "central_units/individual_infos.h"

ArrayXXf IndividualInfos::weight = ArrayXXf();
ArrayXXf IndividualInfos::weightCheckpoint = ArrayXXf();
ArrayXXf IndividualInfos::weightDelta = ArrayXXf();

void IndividualInfos::init(int max_num_individuals, int num_objectives, int max_length)
{

    // init with normal distribution

    IndividualInfos::weight = ArrayXXf::Random((uint32_t)max_num_individuals + 1, (uint32_t)max_length);
    auto mean = IndividualInfos::weight.mean();
    float std = 1 / static_cast<float>(max_length);
    weight -= mean;
    weight *= std;


    IndividualInfos::weightCheckpoint = ArrayXXf((uint32_t)max_num_individuals + 1, (uint32_t)max_length);
    IndividualInfos::weightDelta = ArrayXXf((uint32_t)max_num_individuals + 1, (uint32_t)max_length);
}
