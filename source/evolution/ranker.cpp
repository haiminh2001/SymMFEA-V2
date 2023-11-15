#include "evolution/ranker.h"
#include "central_units/individual_infos.h"
#include "utils/array_utils.h"

// return indices in desceding order (best individuals to worst)
Eigen::Array<unsigned long, Eigen::Dynamic, 1> Ranker::call(SubPopulation& subpop)
{
    std::vector<Eigen::Index> indices(subpop.individuals.size());
    for (Eigen::Index i = 0; i < subpop.individuals.size(); ++i)
    {
        indices[i] = subpop.individuals[i].central_id;
    }
    auto objectives = IndividualInfos::objectives(indices, Eigen::all);

    auto obj_rank = rank<float>(objectives(Eigen::all, 0));

    for (Eigen::Index i = 1; i < objectives.cols(); ++i)
    {
        obj_rank = obj_rank + rank<float>(objectives(Eigen::all, i));
    }

    return argsort<long>(-obj_rank.cast<long>());
}