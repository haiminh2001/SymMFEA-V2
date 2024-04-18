#ifndef SYMMFEA_PRIMITIVE_H
#define SYMMFEA_PRIMITIVE_H
#include "components/functions/node.h"
#include "vector"
#include <tuple>

typedef Node* (*NodeFactory)(int index, int arity);


class Primitive{
public:
    std::vector < std::tuple<NodeFactory, int> > functionList;
    Primitive();
    explicit Primitive(std::vector< int > useable_indices);
    Node* sampleNode(int arity_min, int arity_max);
    NodeFactory getFunction(int arity);

private:;
    std::vector< int > useable_indices;
    std::vector< int > possible_num_arities;
    void addNodeFactory(NodeFactory nf, int arity);
    void removeDuplicatePossibleNumArites();
};

#endif //SYMMFEA_PRIMITIVE_H
