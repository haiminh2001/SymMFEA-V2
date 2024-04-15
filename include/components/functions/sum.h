#ifndef SUM_H
#define SUM_H

#include "node.h"

class Sum : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) override;

public:
    explicit Sum(int arity);

    Node *clone() override;
};

#endif