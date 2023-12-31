#include "components/trainer/gradient_optimizer.h"
#include "central_units/individual_infos.h"
#include "vector"

GradientOptimizer::GradientOptimizer(float learning_rate)
{
    this->learning_rate = learning_rate;
}
/// return if deltaW is nan or not
bool GradientOptimizer::backprop(Individual *individual, ArrayXf deltaY)
{
    
    auto tree = individual->genes;

    std::vector<ArrayXf> stack;
    auto root = tree->nodes[tree->nodes.size() - 1];

    ArrayXf vector_deltaY();
    auto signal = root->backprop(deltaY);

    if (tree->length() == 1)
        return false;

    stack.insert(stack.end(), signal.begin(), signal.end());
    for (int i = tree->length() - 2; i >= 0; --i)
    {
        // get the signal on top of the stack
        auto node = tree->nodes[i];
        deltaY = stack[stack.size() - 1];
        stack.pop_back();

        // backprop
        signal = node->backprop(deltaY);
        if (!node->is_leaf())
        {
            stack.insert(stack.end(), signal.begin(), signal.end());
        }
    }

    auto deltaW = this->compute_gradient(individual);

    if (deltaW.isNaN().any()) return true;

    IndividualInfos::weight.row(individual->central_id) -= deltaW * this->learning_rate;
    return false;
}

ArrayXf GradientOptimizer::compute_gradient(Individual* individual)
{
    return IndividualInfos::weightDelta.row(individual->central_id).log();
}