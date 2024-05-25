#ifndef SYMMFEA_MATING_CONTROLLER_H
#define SYMMFEA_MATING_CONTROLLER_H
#include "evolution/population/population.h"
#include "Eigen/Dense"
// #include <unsupported/Eigen/CXX11/Tensor>
// #include <unsupported/Eigen/NNLS>  
#include <memory>
class MatingController{
    private:
        // Eigen::Array<float, -1, -1, > SMP;

        // Eigen::Tensor<in
        // Eigen::Tensor<int, 2> (3, 2) SMP;
        void get_parent_subpopulations(SubPopulation** father_subpop, SubPopulation** mother_subpop);
    public:
        MatingController(int num_subpopulations, int num_operators);
        void get_parents(std::shared_ptr<Individual>* father, std::shared_ptr<Individual>* mother);   
};
#endif // SYMMFEA_MATING_CONTROLLER_H
