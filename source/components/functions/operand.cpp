#include "operand.h"
#include <iostream>
Operand::Operand(int index) : Node(0, index) {
    this->symbol = std::string("x_") + std::to_string(this->index);
}


ArrayXf Operand::eval(std::stack <ArrayXf>& X){
    std::cout<<"Invalid inference of Operand";
    //return just to justify signature
    return X.top();
}