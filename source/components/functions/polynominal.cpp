#include "components/functions/polynominal.h"
#include "utils/random_utils.h"


ArrayXf Polynominal::_forward(std::stack<ArrayXf> &X, bool record_gradient)
{
    auto x = X.top();
    X.pop();

    auto result = x.pow(this->degree);

    if (record_gradient)
    {
        this->inputDelta.clear();

        this->inputDelta.push_back(this->degree * x.pow(this->degree - 1));
    }
    return result;
}

Polynominal::Polynominal() : Node(1)
{
    this->degree = Random::randint(2, 3);
    this->symbol = "p_" + std::to_string(this->degree);
}

Node *Polynominal::clone()
{
    Polynominal *new_node = new Polynominal();
    return new_node;
}