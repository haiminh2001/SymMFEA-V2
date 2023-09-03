#ifndef SUM_H
#define SUM_H


#include "node.h"

class Sum : public Node{
public:
    ArrayXXf eval(std::vector <ArrayXXf> X) override;
    Sum(int arity, int index) : Node(arity, index) {}
};

#endif