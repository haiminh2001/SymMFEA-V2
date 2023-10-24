#ifndef SYMMFEA_TANH_H
#define SYMMFEA_TANH_H

#include "node.h"

class Tanh : public Node{
public:
    explicit Tanh();

    ArrayXf eval(std::stack <ArrayXf>& X) override;

};
#endif //SYMMFEA_TANH_H
