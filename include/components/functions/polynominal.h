#ifndef SYMMFEA_POLYNOMINAL_H
#define SYMMFEA_POLYNOMINAL_H

#include "node.h"


class Polynominal : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) override;
    int degree;

public:
    explicit Polynominal();
    Node *clone() override;
};
#endif // SYMMFEA_POLYNOMINAL_H
