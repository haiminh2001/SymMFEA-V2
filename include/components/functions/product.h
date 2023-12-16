#ifndef PRODUCT_H
#define PRODUCT_H

#include "node.h"

class Product : public Node{
private: 
    ArrayXf _eval(std::stack <ArrayXf>& X) override;
public:
    explicit Product();
    Node * clone() override;

};

#endif
