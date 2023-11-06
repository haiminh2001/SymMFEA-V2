#include "components/tree/tree.h"
#include <utility>
#include <vector>
#include <stack>
#include <graphviz/gvc.h>
#include <fstream>
#include <tuple>

ArrayXf Tree::eval(const ArrayXXf &X)
{
    auto length = this->nodes.size();
    std::stack<ArrayXf> Stack;

    for (int i = 0; i < length; ++i)
    {
        auto node = this->nodes[i];

        ArrayXf val;

        if (node->is_leaf())
        {
            val = node->eval(X);
        }
        else
        {
            val = node->eval(Stack);
        }

        Stack.push(val);
    }

    assert(Stack.size() == 1);
    return Stack.top();
}

int Tree::length()
{
    return this->nodes[this->nodes.size() - 1]->length + 1;
}

int Tree::depth()
{
    return this->nodes[this->nodes.size() - 1]->depth;
}

void Tree::updateNodeMetadata()
{
    auto length = this->nodes.size();
    for (int i = 0; i < length; ++i)
    {
        auto node = this->nodes[i];
        node->depth = 1;
        node->length = node->arity;
        node->id = i;
        if (node->is_leaf())
        {
            continue;
        }

        int j = i - 1;
        int num_children = node->arity;
        for (int k = 0; k < num_children; ++k)
        {
            auto child = this->nodes[j];
            node->length += child->length;
            node->depth = std::max(node->depth, child->depth);
            j -= child->length + 1;
        }

        node->depth += 1;
    }

    assert(this->length() == this->nodes.size());
}

Tree::Tree(std::vector<Node *> nodes)
{
    this->nodes = std::move(nodes);
    this->updateNodeMetadata();
}

void printSubTree(unsigned long x, unsigned long y, std::vector<Node *> nodes,
                  unsigned long index, std::ofstream &outputFile)
{
    // x, y is the position of the node

    auto node = nodes[index];

    outputFile << "\tnode" << index << " [label=\"" << node->symbol.c_str() << "\"];" << std::endl;

    unsigned long cur_index = index - 1;

    for (int i = 0; i < node->arity; ++i)
    {
        unsigned long new_x = x - y / (index + 1);
        unsigned long new_y = y + 50;
        outputFile << "\tnode" << index << " -> node" << cur_index << ";" << std::endl;
        printSubTree(new_x, new_y, nodes, cur_index, outputFile);

        cur_index -= nodes[cur_index]->length + 1;
    }
}

void Tree::visualize()
{
    std::ofstream outputFile("/tmp/tree.dot");
    outputFile << "digraph Tree {" << std::endl;
    printSubTree(300, 100, this->nodes, this->nodes.size() - 1, outputFile);
    outputFile << "}" << std::endl;
    outputFile.close();
    std::system("dot -Tpng /tmp/tree.dot -o tree.png");
};

std::tuple<std::vector<Node>, std::tuple<std::vector<Node>, std::vector<Node>>> Tree::split_tree(int split_point)
{
    // NOTE: test this function 
    std::vector<Node> branch(this->nodes.begin() + split_point - this->nodes[split_point]->length, this->nodes.begin() + split_point);
    std::vector<Node> root1(this->nodes.begin(), this->nodes.begin() + split_point - this->nodes[split_point]-> length);
    std::vector<Node> root2(this->nodes.begin() + split_point - this->nodes[split_point]-> length + 1, this->nodes.end());
    return std::make_tuple(branch, std::make_tuple(root1, root2));
}