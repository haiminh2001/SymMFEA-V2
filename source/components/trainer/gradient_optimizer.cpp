#include "components/trainer/gradient_optimizer.h"
#include "central_units/individual_infos.h"
#include <stack>

GradientOptimizer::GradientOptimizer(float learning_rate)
{
    this->learning_rate = learning_rate;
}
/// return if deltaW is nan or not
bool GradientOptimizer::backprop(Individual *individual, ArrayXf deltaY)
{
    
    auto tree = individual->genes;

    std::stack<ArrayXf> Stack;
    auto root = tree->nodes[tree->nodes.size() - 1];

    auto signal = root->backprop(deltaY);

    if (tree->length() == 1)
        return false;

    for (const auto& s :signal) Stack.push(s);
    
    for (int i = tree->length() - 2; i >= 0; --i)
    {
        // get the signal on top of the stack
        auto node = tree->nodes[i];
        deltaY = Stack.top();
        Stack.pop();

        // backprop
        signal = node->backprop(deltaY);
        if (!node->is_leaf())
        {
            for (const auto & s :signal) Stack.push(s);
        }
    }

    // the stack should be empty after consume all the signals
    assert (Stack.empty());

    auto deltaW = this->compute_gradient(individual);

    if (deltaW.isNaN().any()) return true;

    IndividualInfos::weight.row(individual->central_id) -= deltaW * this->learning_rate;
    return false;
}

ArrayXf GradientOptimizer::compute_gradient(Individual* individual)
{
    // use logarit to prevent overflow
    return IndividualInfos::weightDelta.row(individual->central_id).log();
}