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
            delete individual;
        }
    };

    IndividualNode *successor(IndividualNode *node);

    // function to perform BST insertion of a Node
    IndividualNode *binary_search_tree_insert(IndividualNode *root, IndividualNode *temp);

    class RedBlackTree
    {
    private:
        IndividualNode *root;

        // Function performing right rotation
        // of the passed Node
        void rightrotate(IndividualNode *temp)
        {
            IndividualNode *left = temp->left;
            temp->left = left->right;
            if (temp->left)
                temp->left->parent = temp;
            left->parent = temp->parent;
            if (!temp->parent)
                root = left;
            else if (temp == temp->parent->left)
                temp->parent->left = left;
            else
                temp->parent->right = left;
            left->right = temp;
            temp->parent = left;
        }

        // Function performing left rotation
        // of the passed Node
        void leftrotate(IndividualNode *temp)
        {
            IndividualNode *right = temp->right;
            temp->right = right->left;
            if (temp->right)
                temp->right->parent = temp;
            right->parent = temp->parent;
            if (!temp->parent)
                root = right;
            else if (temp == temp->parent->left)
                temp->parent->left = right;
            else
                temp->parent->right = right;
            right->left = temp;
            temp->parent = right;
        }

        // This function fixes violations
        // caused by BST insertion
        void fixup(IndividualNode *pt)
        {
            IndividualNode *parent_pt = nullptr;
            IndividualNode *grand_parent_pt = nullptr;

            while ((pt != root) && (pt->color != NodeColor::BLACK) && (pt->parent->color == NodeColor::RED))
            {
                parent_pt = pt->parent;
                grand_parent_pt = pt->parent->parent;

                /*  Case : A
                     Parent of pt is left child
                     of Grand-parent of
                   pt */
                if (parent_pt == grand_parent_pt->left)
                {

                    IndividualNode *uncle_pt = grand_parent_pt->right;

                    /* Case : 1
                        The uncle of pt is also red
                        Only Recoloring required */
                    if (uncle_pt != nullptr && uncle_pt->color == NodeColor::RED)
                    {
                        grand_parent_pt->color = NodeColor::RED;
                        parent_pt->color = NodeColor::BLACK;
                        uncle_pt->color = NodeColor::BLACK;
                        pt = grand_parent_pt;
                    }

                    else
                    {

                        /* Case : 2
                             pt is right child of its parent
                             Left-rotation required */
                        if (pt == parent_pt->right)
                        {
                            leftrotate(parent_pt);
                            pt = parent_pt;
                            parent_pt = pt->parent;
                        }

                        /* Case : 3
                             pt is left child of its parent
                             Right-rotation required */
                        rightrotate(grand_parent_pt);
                        auto t = parent_pt->color;
                        parent_pt->color = grand_parent_pt->color;
                        grand_parent_pt->color = t;
                        pt = parent_pt;
                    }
                }

                /* Case : B
                     Parent of pt is right
                     child of Grand-parent of
                   pt */
                else
                {
                    IndividualNode *uncle_pt = grand_parent_pt->left;

                    /*  Case : 1
                        The uncle of pt is also red
                        Only Recoloring required */
                    if ((uncle_pt != nullptr) && (uncle_pt->color == NodeColor::RED))
                    {
                        grand_parent_pt->color = NodeColor::RED;
                        parent_pt->color = NodeColor::BLACK;
                        uncle_pt->color = NodeColor::BLACK;
                        pt = grand_parent_pt;
                    }
                    else
                    {
                        /* Case : 2
                           pt is left child of its parent
                           Right-rotation required */
                        if (pt == parent_pt->left)
                        {
                            rightrotate(parent_pt);
                            pt = parent_pt;
                            parent_pt = pt->parent;
                        }

                        /* Case : 3
                             pt is right child of its parent
                             Left-rotation required */
                        leftrotate(grand_parent_pt);
                        auto t = parent_pt->color;
                        parent_pt->color = grand_parent_pt->color;
                        grand_parent_pt->color = t;
                        pt = parent_pt;
                    }
                }
            }
        }

    public:
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        void bfsPrint()
        {

            std::queue<IndividualNode *> queue;

            queue.push(root);

            while (!queue.empty())
            {

                auto current_node = queue.front();
                queue.pop();
                if (current_node->left || current_node->right)
                {
                    std::cout << current_node->value << ": ";
                    if (current_node->left)
                    {
                        queue.push(current_node->left);
                        std::cout << current_node->left->value << " ";
                    }
                    if (current_node->right)
                    {
                        queue.push(current_node->right);
                        std::cout << current_node->right->value;
                    }
                    std::cout << "\n";
                }
            }
        }

        // Function to insert a node into the Red-Black Tree
        void insert(IndividualNode *node)
        {
            this->root = binary_search_tree_insert(root, node);
            this->fixup(node);
            this->root->color = NodeColor::BLACK;
            this->num_nodes++;
        }

        // Function to remove the smallest node
        void remove_smallest_node()
        {
            if (root == nullptr)
                return;

            IndividualNode *node = root;
            IndividualNode *p;
            while (node->left != nullptr)
            {
                p = node;
                node = node->left;
            }
            p->left = node->right;
            delete node;
        }
        // Function to get the largest node
        IndividualNode *get_largest_node()
        {
            if (root == nullptr)
                return nullptr;

            IndividualNode *node = root;

            while (node->right != nullptr)
            {
                node = node->right;
            }
            return node;
        }
        // NOTE: may implement a different logic to handle different height of the tree
        IndividualNode *get_random_node()
        {
            if (root == nullptr)
                return nullptr;

            IndividualNode *node = root;
            uint8_t direction;

            while (true)

            { // probability of choosing the left child, current node or the right child
                std::vector<float> direction_probs;

                if (node->left)
                    direction_probs.push_back(1);
                else
                    direction_probs.push_back(0);

                direction_probs.push_back(4);

                if (node->right)
                    direction_probs.push_back(10);
                else
                    direction_probs.push_back(0);

                direction = Random::random_choice<int>(direction_probs);

                if (direction == 2)
                    node = node->right;
                else if (direction == 1)
                    break;
                else
                    node = node->left;
            }

            return node;
        }
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
