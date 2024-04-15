#ifndef PRODUCT_H
#define PRODUCT_H

#include "node.h"

class Product : public Node{
private: 
    ArrayXf _forward(std::stack <ArrayXf>& X, bool record_gradient) override;
public:
    explicit Product();
    Node * clone() override;

};

#endif
