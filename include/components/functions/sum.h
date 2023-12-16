#ifndef SUM_H
#define SUM_H

#include "node.h"

class Sum : public Node
{
private:
    ArrayXf _eval(std::stack<ArrayXf> &X) override;

public:
    explicit Sum(int arity);

    Node *clone() override;
};

#endif