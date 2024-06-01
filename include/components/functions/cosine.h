#ifndef SYMMFEA_COSINE_H
#define SYMMFEA_COSINE_H

#include "node.h"

class Cosine : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) override;

public:
    explicit Cosine();
    Node *clone() override;
};
#endif // SYMMFEA_COSINE_H
