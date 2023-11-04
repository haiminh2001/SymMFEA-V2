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
    Primitive(int max_index);
    Node* sampleNode(int arity_min, int arity_max);
    NodeFactory getFunction(int arity);

private:
    int max_index;
    std::vector< int > possibleArities;
    void addNodeFactory(NodeFactory nf, int arity);
    void removeDuplicatePossibleArites();
};

#endif //SYMMFEA_PRIMITIVE_H
