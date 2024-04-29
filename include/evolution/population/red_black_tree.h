#ifndef SYMMFEA_RED_BLACK_TREE_H
#define SYMMFEA_RED_BLACK_TREE_H
#include "evolution/population/individual.h"
#include "utils/random_utils.h"
#include <iostream>
#include <queue>
#include <mutex>

namespace RedBlackTree
{
    enum class NodeColor
    {
        RED,
        BLACK
    };

    class IndividualNode
    {
    private:
        std::mutex lock;

    public:
        Individual *individual;
        float value;
        IndividualNode *parent;
        IndividualNode *left;
        IndividualNode *right;
        NodeColor color;

        IndividualNode() : individual(nullptr), parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
        ~IndividualNode()
        {
            this->lock.lock();
            delete this->individual;
            this->lock.unlock();
        }
    };

    IndividualNode *successor(IndividualNode *node);

    // function to perform BST insertion of a Node
    IndividualNode *binary_search_tree_insert(IndividualNode *root, IndividualNode *temp);

    class RedBlackTree
    {
    private:
        std::mutex lock;
        IndividualNode *root;

        // Function performing right rotation
        // of the passed Node
        void right_rotate(IndividualNode *temp);

        // Function performing left rotation
        // of the passed Node
        void left_rotate(IndividualNode *temp);

        // This function fixes violations
        // caused by BST insertion
        void fixup(IndividualNode *pt);

    public:
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        std::string bfsPrint();

        // Function to insert a node into the Red-Black Tree
        void insert(IndividualNode *node);

        // Function to remove the smallest node
        void remove_smallest_node();

        // Function to get the largest node
        IndividualNode *get_largest_node();

                IndividualNode *get_random_node();
    };

    // test:
    // int main()
    // {
    //     int n = 7;
    //     int a[7] = {7, 6, 5, 4, 3, 2, 1};

    //     RedBlackTree tree = RedBlackTree();

    //     Node *t;
    //     for (int i = 0; i < n; i++)
    //     {

    //         Node *temp = new Node(a[i]);

    //         if (i == 2)
    //             t = temp;
    //         tree.insert(temp);
    //     }

    //     tree.remove(t);

    //     tree.bfsPrint();

    //     return 0;
    // }
}

#endif // SYMMFEA_RED_BLACK_TREE_H
