#include "individual.h"



Individual::Individual(Tree* genes, int skill_factor){
    this->genes = genes;
    this->skill_factor = skill_factor;
}

ArrayXf Individual::eval(const ArrayXXf& X) const{
    return this->genes->eval(X);
};
