#ifndef SUM_H
#define SUM_H


#include "node.h"

class Sum : public Node{
public:
    ArrayXf eval(std::stack <ArrayXf>& X) override;

    explicit Sum(int arity);

Node * clone() override;
    
};

#endif