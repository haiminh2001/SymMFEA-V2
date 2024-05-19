#ifndef SYMMFEA_RED_BLACK_TREE_H
#define SYMMFEA_RED_BLACK_TREE_H
#include "evolution/population/individual.h"
#include "utils/random_utils.h"

#include <queue>
#include <mutex>
#include <memory>
#include <iostream>

namespace RedBlackTree
{
    enum class NodeColor
    {
        RED,
        BLACK
    };

    template <typename T>
    class IndividualNode
    {
    private:
    public:
        T data;
        float value;
        IndividualNode *parent;
        IndividualNode *left;
        IndividualNode *right;
        NodeColor color;

        bool is_left_child_black_or_null()
        {
            return (this->left == nullptr || this->left->color == NodeColor::BLACK);
        }
        bool is_right_child_black_or_null()
        {
            return (this->right == nullptr || this->right->color == NodeColor::BLACK);
        }
        bool is_left_child()
        {
            if (this->parent == nullptr)
                return false;

            return this->parent->left == this;
        }
        bool is_right_child()
        {
            if (this->parent == nullptr)
                return false;

            return this->parent->right == this;
        }

        std::string color_string()
        {
            return this->color == NodeColor::RED ? "RED" : "BLACK";
        }

        // Default color of a new node is red
        IndividualNode() : parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
        IndividualNode(T data) : IndividualNode()
        {
            this->data = data;
        }
    };

    template <typename T>
    IndividualNode<T> *successor(IndividualNode<T> *node)
    {
        if (node->right != nullptr)
        {
            // If the node has a right child, find the leftmost node in the right subtree
            IndividualNode<T> *current = node->right;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }
        else
        {
            // If the node does not have a right child, find the first ancestor that is a left child
            IndividualNode<T> *ancestor = node->parent;
            while ((ancestor != nullptr) && ancestor->is_right_child())
            {
                ancestor = ancestor->parent;
            }
            return ancestor;
        }
    }

    // function to perform BST insertion of a Node
    template <typename T>
    IndividualNode<T> *binary_search_tree_insert(IndividualNode<T> *root, IndividualNode<T> *temp)
    {
        // If the tree is empty,
        // return a new Node
        if (!root)
            return temp;

        // Otherwise recur down the tree
        if (temp->value < root->value)
        {
            root->left = binary_search_tree_insert(root->left, temp);
            root->left->parent = root;
        }
        else
        {
            root->right = binary_search_tree_insert(root->right, temp);
            root->right->parent = root;
        }

        // Return the (unchanged) Node pointer
        return root;
    }

    template <typename T>
    class RedBlackTree
    {
    private:
        std::mutex lock;

    public:
        void swap_position_on_tree(IndividualNode<T> *a, IndividualNode<T> *b)
        {
            // swap root if one of the nodes is root
            IndividualNode<T> *temp;
            if (this->root == a)
            {
                this->root = b;
            }
            else if (this->root == b)
            {
                this->root = a;
            }

            // swap parent
            if (b->parent)
            {
                if (b->is_left_child())
                    b->parent->left = a;
                else
                    b->parent->right = a;
            }
            if (a->parent)
            {
                if (a->is_left_child())
                    a->parent->left = b;
                else
                    a->parent->right = b;
            }
            temp = a->parent;
            a->parent = b->parent;
            b->parent = temp;

            // swap left child
            temp = a->left;
            a->left = b->left;
            if (a->left)
                a->left->parent = a;

            b->left = temp;
            if (b->left)
                b->left->parent = b;

            // swap right child
            temp = a->right;
            a->right = b->right;
            if (a->right)
                a->right->parent = a;

            b->right = temp;
            if (b->right)
                b->right->parent = b;

            // auto temp_color = a->color;
            // a->color = b->color;
            // b->color = temp_color;
        }

        // no validation, assume that the node is on the tree
        // return the color of the node that was deleted and the node that is replacing it
        void binary_search_tree_delete(IndividualNode<T> *node,
                                       NodeColor *deleted_node_color = nullptr,
                                       IndividualNode<T> **replacing_node = nullptr,
                                       IndividualNode<T> **parent_of_replacing_node = nullptr)
        {
            if (node == nullptr)
                throw std::runtime_error("Invalid node to delete");

            // leaf node
            if ((node->left == nullptr) && (node->right == nullptr))
            {
                if (node->is_left_child())
                {
                    node->parent->left = nullptr;
                }
                else
                {
                    node->parent->right = nullptr;
                }

                // delete node and return
                if (deleted_node_color)
                {
                    *deleted_node_color = node->color;
                }
                if (replacing_node)
                {
                    // no children, so no replacement
                    *replacing_node = nullptr;
                    *parent_of_replacing_node = node->parent;
                }
                delete node;
            }

            // one-child node
            else if ((node->left == nullptr) || (node->right == nullptr))
            {
                IndividualNode<T> *child = (node->left == nullptr) ? node->right : node->left;

                // if the node does not have parent, then it should be the root
                if (node->parent == nullptr)
                {
                    this->root = child;
                }
                else
                {
                    // detach the node from the tree
                    if (node->is_left_child())
                    {
                        node->parent->left = child;
                    }
                    else
                    {
                        node->parent->right = child;
                    }
                }

                child->parent = node->parent;

                // delete node and return
                if (deleted_node_color)
                {
                    *deleted_node_color = node->color;
                }
                if (replacing_node)
                {
                    *replacing_node = child;
                }
                delete node;
            }

            else // two-child node
            {
                IndividualNode<T> *successor_node = successor(node);
                if (successor_node == nullptr)
                    throw std::runtime_error("Invalid succesorr node");
                this->swap_position_on_tree(node, successor_node);
                this->binary_search_tree_delete(node, deleted_node_color, replacing_node, parent_of_replacing_node);
            }
        }

        // Function performing right rotation of the subtree with the root node is passed
        void right_rotate(IndividualNode<T> *rotation_point)
        {
            IndividualNode<T> *left = rotation_point->left;

            assert(left != nullptr && "Invalid right rotation, no left child!!");

            // attach the left node to the parent of the current node
            left->parent = rotation_point->parent;
            if (rotation_point == this->root)
            {
                root = left;
            }
            else
            {
                if (rotation_point->is_left_child())
                {
                    rotation_point->parent->left = left;
                }
                else
                {
                    rotation_point->parent->right = left;
                }
            }
            // attach the right of the left child to the left of the temp node
            rotation_point->left = left->right;
            if (left->right != nullptr)
            {
                left->right->parent = rotation_point;
            }

            // attach the temp node as the right child of the left node
            left->right = rotation_point;
            rotation_point->parent = left;
        }

        // Function performing right rotation of the subtree with the root node is passed
        void left_rotate(IndividualNode<T> *rotation_point)
        {
            IndividualNode<T> *right = rotation_point->right;

            assert(right != nullptr && "Invalid left rotation, no right child!!");

            // attach the right node to the parent of the current node
            right->parent = rotation_point->parent;
            if (rotation_point == this->root)
            {
                root = right;
            }
            else
            {
                if (rotation_point->is_left_child())
                {
                    rotation_point->parent->left = right;
                }
                else
                {
                    rotation_point->parent->right = right;
                }
            }
            // attach the left of the right child to the right of the temp node
            rotation_point->right = right->left;

            if (right->left != nullptr)
            {
                right->left->parent = rotation_point;
            }

            // attach the temp node as the left child of the right node
            right->left = rotation_point;
            rotation_point->parent = right;
        }

        // This function fixes violations
        // caused by BST insertion
        // reference: https://www.programiz.com/dsa/insertion-in-a-red-black-tree
        void fixup_insert_violations(IndividualNode<T> *new_node)
        {
            IndividualNode<T> *parent = nullptr;
            IndividualNode<T> *grandparent = nullptr;
            IndividualNode<T> *uncle = nullptr;

            while ((new_node != this->root) && (new_node->parent->color == NodeColor::RED))
            {
                parent = new_node->parent;
                grandparent = new_node->parent->parent;
                uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;

                /*  Case : A
                Parent of new_node is left child
                of Grand-parent of new_node */
                if (parent->is_left_child())
                {
                    /* Case-I*/
                    if (uncle != nullptr && uncle->color == NodeColor::RED)
                    {
                        grandparent->color = NodeColor::RED;
                        parent->color = NodeColor::BLACK;
                        uncle->color = NodeColor::BLACK;
                        new_node = grandparent;
                    }

                    else
                    {
                        /* Case-II*/
                        if (new_node->is_right_child())
                        {
                            new_node = parent;
                            this->left_rotate(new_node);
                        }

                        /* Case-III */
                        else
                        {
                            parent->color = NodeColor::BLACK;
                            grandparent->color = NodeColor::RED;
                            this->right_rotate(grandparent);
                        }
                    }
                }

                /* Case : B
                Parent of new_node is right
                child of Grand-parent of
                new_node */
                else
                {
                    /* Case-I*/
                    if (uncle != nullptr && uncle->color == NodeColor::RED)
                    {
                        grandparent->color = NodeColor::RED;
                        parent->color = NodeColor::BLACK;
                        uncle->color = NodeColor::BLACK;
                        new_node = grandparent;
                    }
                    else
                    {
                        /* Case-II*/
                        if (new_node->is_left_child())
                        {
                            new_node = parent;
                            this->right_rotate(new_node);
                        }

                        /* Case-III */
                        else
                        {
                            parent->color = NodeColor::BLACK;
                            grandparent->color = NodeColor::RED;
                            this->left_rotate(grandparent);
                        }
                    }
                }
            }
            this->root->color = NodeColor::BLACK;
        }

        /*
            Fix up the violations occuring after the binary search tree deletion.
            Reference: https://www.programiz.com/dsa/deletion-from-a-red-black-tree
        */
        void fixup_delete_violations(IndividualNode<T> *x, IndividualNode<T> *x_parent, bool x_is_left_child)
        {
            IndividualNode<T> *s = nullptr;

            while ((x == nullptr) || (x != this->root && x->color == NodeColor::BLACK))
            {
                // get the s and x parent
                if (x == nullptr)
                {
                    s = x_is_left_child ? x_parent->right : x_parent->left;
                }
                else
                {
                    s = x->is_left_child() ? x->parent->right : x->parent->left;
                    x_parent = x->parent;
                }

                if ((x == nullptr && x_is_left_child) || ((x != nullptr) && (x->is_left_child())))
                {
                    if (s->color == NodeColor::RED)
                    {
                        s->color = NodeColor::BLACK;
                        x_parent->color = NodeColor::RED;
                        this->left_rotate(x_parent);
                        s = x_parent->right;
                    }
                    if (s->is_left_child_black_or_null() && s->is_right_child_black_or_null())
                    {
                        s->color = NodeColor::RED;
                        x = x_parent;
                    }
                    else
                    {
                        if (s->is_right_child_black_or_null())
                        {
                            if (s->left != nullptr)
                            {
                                s->left->color = NodeColor::BLACK;
                            }
                            s->color = NodeColor::RED;
                            this->right_rotate(s);
                            s = x_parent->right;
                        }
                        s->color = x_parent->color;
                        x_parent->color = NodeColor::BLACK;
                        s->right->color = NodeColor::BLACK;
                        this->left_rotate(x_parent);
                        x = this->root;
                    }
                }
                else
                {
                    if (s->color == NodeColor::RED)
                    {
                        s->color = NodeColor::BLACK;
                        x_parent->color = NodeColor::RED;
                        this->right_rotate(x_parent);
                        s = x_parent->left;
                    }
                    if (s->is_left_child_black_or_null() && s->is_right_child_black_or_null())
                    {
                        s->color = NodeColor::RED;
                        x = x_parent;
                    }
                    else
                    {
                        if (s->is_left_child_black_or_null())
                        {
                            if (s->right != nullptr)
                            {
                                s->right->color = NodeColor::BLACK;
                            }
                            s->color = NodeColor::RED;
                            this->left_rotate(s);
                            s = x_parent->left;
                        }
                        s->color = x_parent->color;
                        x_parent->color = NodeColor::BLACK;

                        if (s->left != nullptr)
                        {
                            s->left->color = NodeColor::BLACK;
                        }
                        this->right_rotate(x_parent);
                        x = this->root;
                    }
                }
            }
            x->color = NodeColor::BLACK;
        }

        IndividualNode<T> *root;
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        std::string bfsPrint()
        {
            if (this->root == nullptr) return "NULL TREE\n";

            std::string result = "";
            std::queue<IndividualNode<T> *> queue;

            queue.push(root);

            while (!queue.empty())
            {

                auto current_node = queue.front();
                queue.pop();
                if (current_node->left || current_node->right)
                {

                    result += std::to_string(current_node->value) + "(" + current_node->color_string() + ") " + ": ";
                    if (current_node->left)
                    {
                        queue.push(current_node->left);
                        result += std::to_string(current_node->left->value) + "(" + current_node->left->color_string() + ") " + " ";
                    }
                    if (current_node->right)
                    {
                        queue.push(current_node->right);

                        result += std::to_string(current_node->right->value) + "(" + current_node->right->color_string() + ") " + " ";
                    }
                    result += '\n';
                }
            }
            return result;
        }

        // Function to insert a node into the Red-Black Tree
        void insert(IndividualNode<T> *node)
        {
            std::lock_guard<std::mutex> lock(this->lock);
            this->root = binary_search_tree_insert(root, node);
            this->fixup_insert_violations(node);
            this->num_nodes++;
        }

        /// @brief Transplant subtree v into u position
        /// @param u
        /// @param v
        void rbTransplant(IndividualNode<T> *u, IndividualNode<T> *v)
        {
            if (this->root == u)
                this->root = v;
            else if (u->is_left_child())
                u->parent->left = v;
            else
                u->parent->right = v;

            if (v != nullptr)
                v->parent = u->parent;
        }

        void remove(IndividualNode<T> *z)
        {
            std::lock_guard<std::mutex> lock(this->lock);
            assert(z != nullptr && "Invalid node to delete");
            if (z == this->root && this->num_nodes == 1){
                this->root = nullptr;
            }
            else
            {
                IndividualNode<T> *y = nullptr, *x = nullptr, *x_parent = nullptr;
                bool x_is_left_child;
                y = z;
                NodeColor y_originalColor = y->color;

                // if the node has only one or no children
                if (z->left == nullptr)
                {
                    x = z->right;
                    x_parent = z->parent;
                    x_is_left_child = false;
                    this->rbTransplant(z, x);
                }
                else if (z->right == nullptr)
                {
                    x = z->left;
                    x_parent = z->parent;
                    x_is_left_child = true;
                    this->rbTransplant(z, x);
                }

                // the node has two children
                else
                {
                    // find smallest node in the right subtree
                    y = z->right;
                    while (y->left != nullptr)
                        y = y->left;

                    y_originalColor = y->color;
                    x = y->right;
                    x_parent = y;
                    x_is_left_child = false;

                    // if (y->parent == z)
                    // {
                    //     x_parent = y;
                    // }
                    if (y->parent != z)
                    // else
                    {
                        x_is_left_child = y->is_left_child();
                        this->rbTransplant(y, x);
                        x_parent = y->parent;
                        

                        y->right = z->right;
                        y->right->parent = y;
                    }
                    this->rbTransplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }

                if (y_originalColor == NodeColor::BLACK)
                    this->fixup_delete_violations(x, x_parent, x_is_left_child);
            }

            delete z;
            this->num_nodes--;
        }

        // Function to remove the smallest node
        void remove_smallest_node()
        {
            std::lock_guard<std::mutex> lock(this->lock);
            if (root == nullptr)
                return;

            IndividualNode<T> *node = root;
            IndividualNode<T> *p;
            while (node->left != nullptr)
            {
                p = node;
                node = node->left;
            }
            p->left = node->right;
            delete node;
            this->num_nodes--;
        }

        // Function to get the largest node
        IndividualNode<T> *get_largest_node()
        {
            if (root == nullptr)
                return nullptr;

            IndividualNode<T> *node = root;

            while (node->right != nullptr)
            {
                node = node->right;
            }
            return node;
        }

        // NOTE: may implement a different logic to handle different height of the tree
        IndividualNode<T> *get_random_node()
        {
            if (this->root == nullptr)
                return nullptr;

            IndividualNode<T> *node = this->root;
            int direction;

            while (true)

            { // probability of choosing the left child, current node or the right child
                std::vector<float> direction_probs;

                if (node->left != nullptr)
                    direction_probs.push_back(1);
                else
                    direction_probs.push_back(0);

                direction_probs.push_back(4);

                if (node->right != nullptr)
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

}

#endif // SYMMFEA_RED_BLACK_TREE_H
