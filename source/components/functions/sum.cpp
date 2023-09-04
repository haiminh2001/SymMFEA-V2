#include <vector>
#include "sum.h"


ArrayXf Sum::eval(std::stack <ArrayXf>& X){
    ArrayXf result = X.top();
    X.pop();

    auto num_operands = this->arity - 1;
    while (num_operands > 0){
        result = result + X.top();
        X.pop();
        num_operands--;
    }
    return result;
}

Sum::Sum(int arity) : Node(arity) {
    this->symbol = "+";
}
