#include "components/functions/silu.h"


ArrayXf Sigmoid(ArrayXf x)
{
    return 1 / (1 + (-x).exp());
}


ArrayXf Silu::_forward(std::stack<ArrayXf> &X, bool record_gradient)
{
    auto x = X.top();
    X.pop();

    auto sigmoid = Sigmoid(x);

    auto result = x * sigmoid;

    if (record_gradient)
    {
        this->inputDelta.clear();

        
        this->inputDelta.push_back(sigmoid + x * sigmoid * (1 - sigmoid));
    }
    return result;
}

Silu::Silu() : Node(1)
{
    this->symbol = "Silu";
}

Node *Silu::clone()
{
    Silu *new_node = new Silu();
    return new_node;
}