#include "tree.h"
#include <utility>
#include <vector>
#include <stack>
#include <graphics.h>
#include <iostream>

ArrayXf Tree::eval(const ArrayXXf& X){
    auto length = this->nodes.size();
    std::stack <ArrayXf> Stack;

    for (int i = 0; i < length; ++i){
        auto node = this->nodes[i];

        ArrayXf val;

        if (node->is_leaf()){
            val = node->eval(X);
        }
        else{
            val = node->eval(Stack);
        }

        Stack.push(val);
    }

    assert(Stack.size() == 1);
    return Stack.top();

}

int Tree::length(){
    return this->nodes[this->nodes.size() - 1]->length + 1;
}

void Tree::updateNodeMetadata(){
    auto length = this->nodes.size();
    for (int i = 0; i < length; ++i){
        auto node = this->nodes[i];
        node->depth = 1;
        node->length = node->arity;
        node->id = i;
        if (node->is_leaf()){
            continue;
        }

        int j = i - 1;
        int num_children = node->arity;
        for (int k = 0; k < num_children; ++k){
            auto child = this->nodes[j];
            node->length += child->length;
            node->depth = std::max(node->depth, child->depth);
            j-= child->length + 1;
        }

        node->depth += 1;

    }

    assert (this->length() == this->nodes.size());
}

Tree::Tree(std::vector<Node*> nodes){
    this->nodes = std::move(nodes);
    this->updateNodeMetadata();
}

void printSubTree(unsigned long x, unsigned long y, std::vector <Node*> nodes,
                  unsigned long index)
{
    //x, y is the position of the node

    auto node = nodes[index];

    // Set color of the boundary of
    // circle as green
    setcolor(GREEN);

    // Draw the circle of radius 15
    // that represent node of Tree
    circle(x, y, 15);
    floodfill(x, y, GREEN);

    // Print the values of the node
    // in the circle

    char* node_content = const_cast<char *> (node->symbol.c_str());

    outtextxy(x - 2, y - 3, node_content);

    // Set the color of the line
    // from parent to child as green
    setcolor(GREEN);

    unsigned long cur_index = index - 1;

    for (int i = 0; i < node->arity; ++i){
        unsigned long new_x = x - y / (index + 1);
        unsigned long new_y = y + 50;
        printSubTree(new_x, new_y, nodes, cur_index);

        cur_index -= nodes[cur_index]->length + 1;
//        draw edge
        line(x, y, new_x, new_y);
    }

}

void Tree::visualize(){
    int gd = DETECT, gm;
    auto driver = const_cast<char *> ("None");

    initgraph(&gd, &gm, driver);
    auto a =5;
    printSubTree(300, 100, this->nodes,this->nodes.size() - 1);
    getch();
    closegraph();
};


