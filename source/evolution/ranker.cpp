#include "evolution/ranker.h"
#include "central_units/individual_infos.h"
#include "utils/array_utils.h"

using namespace ArrayUtils;

// return indices in desceding order (best individuals to worst)
Eigen::Array<unsigned long, Eigen::Dynamic, 1> Ranker::call(SubPopulation &subpop)
{
    auto indices = subpop.get_central_ids();
    auto objectives = IndividualInfos::objectives(indices, Eigen::all);

    auto obj_rank = rank<float>(objectives(Eigen::all, 0));

    for (Eigen::Index i = 1; i < objectives.cols(); ++i)
    {
        obj_rank = obj_rank + rank<float>(objectives(Eigen::all, i));
    }

    return argsort<long>(-obj_rank.cast<long>());
}
