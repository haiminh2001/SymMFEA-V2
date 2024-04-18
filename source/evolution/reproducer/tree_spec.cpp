#include "evolution/reproducer/tree_spec.h" 

TreeSpec::TreeSpec(std::vector<int> usable_indices, int max_length, int max_depth)
{
    this->usable_indices = usable_indices;
    this->max_length = max_length;
    this->max_depth = max_depth;
}

TreeSpec::TreeSpec(int max_indice, int max_length, int max_depth)
{
    this->usable_indices = std::vector<int>(max_indice);
    for (int i = 0; i < max_indice; i++)
    {
        this->usable_indices[i] = i;
    }
    this->max_length = max_length;
    this->max_depth = max_depth;
}

TreeSpec::TreeSpec(TreeSpec* other){
    this->usable_indices = other->usable_indices;
    this->max_length = other->max_length;
    this->max_depth = other->max_depth;
}