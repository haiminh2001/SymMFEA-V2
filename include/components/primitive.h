#ifndef SYMMFEA_PRIMITIVE_H
#define SYMMFEA_PRIMITIVE_H
#include "node.h"
#include "vector"
#include <tuple>

typedef Node* (*NodeFactory)(int index, int arity);


class Primitive{
public:
    std::vector < std::tuple<NodeFactory, int> > functionList;
    Primitive();

    NodeFactory getFunction(int arity);
};

#endif //SYMMFEA_PRIMITIVE_H
