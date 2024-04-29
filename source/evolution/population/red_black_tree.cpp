#include "evolution/population/red_black_tree.h"

namespace RedBlackTree
{
    IndividualNode::IndividualNode(std::shared_ptr<Individual> individual) : IndividualNode()
    {
        this->individual = individual;
    }
    IndividualNode *successor(IndividualNode *node)
    {
        if (node->right != nullptr)
        {
            // If the node has a right child, find the leftmost node in the right subtree
            IndividualNode *current = node->right;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }
        else
        {
            // If the node does not have a right child, find the first ancestor that is a left child
            IndividualNode *parent = node->parent;
            while (parent != nullptr && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }

    void swap_position_on_tree(IndividualNode *a, IndividualNode *b)
    {

        if (b->parent)
        {
            if (b->parent->left == b)
                b->parent->left = a;
            else
                b->parent->right = a;
        }
        if (a->parent)
        {
            if (a->parent->left == a)
                a->parent->left = b;
            else
                a->parent->right = b;
        }
        IndividualNode *temp = a->parent;
        a->parent = b->parent;
        b->parent = temp;

        temp = a->left;
        a->left = b->left;
        if (a->left)
            a->left->parent = a;

        b->left = temp;
        if (b->left)
            b->left->parent = b;

        temp = a->right;
        a->right = b->right;
        if (a->right)
            a->right->parent = a;

        b->right = temp;
        if (b->right)
            b->right->parent = b;
    }

    void binary_search_tree_delete(IndividualNode *node)
    {
        if (node == nullptr)
            return;

        if ((!node->left) && (!node->right))
        {
            if (node->parent)
            {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
            delete node;
        }
        else if ((!node->left) || (!node->right))
        {
            IndividualNode *child = node->left ? node->left : node->right;
            if (node->parent)
            {
                if (node->parent->left == node)
                    node->parent->left = child;
                else
                    node->parent->right = child;
            }
            delete node;
        }

        else
        {
            IndividualNode *successor_node = successor(node);
            
            swap_position_on_tree(node, successor_node);

            binary_search_tree_delete(node);
        }
    }

    IndividualNode *binary_search_tree_insert(IndividualNode *root,
                                              IndividualNode *temp)
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
        else if (temp->value > root->value)
        {
            root->right = binary_search_tree_insert(root->right, temp);
            root->right->parent = root;
        }

        // Return the (unchanged) Node pointer
        return root;
    }

    void RedBlackTree::right_rotate(IndividualNode *temp)
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

    void RedBlackTree::left_rotate(IndividualNode *temp)
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
    }

    void RedBlackTree::fixup(IndividualNode *pt)
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
                        left_rotate(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3
                         pt is left child of its parent
                         Right-rotation required */
                    right_rotate(grand_parent_pt);
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
                        right_rotate(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3
                         pt is right child of its parent
                         Left-rotation required */
                    left_rotate(grand_parent_pt);
                    auto t = parent_pt->color;
                    parent_pt->color = grand_parent_pt->color;
                    grand_parent_pt->color = t;
                    pt = parent_pt;
                }
            }
        }
    }

    std::string RedBlackTree::bfsPrint()
    {
        std::string result = "";
        std::queue<IndividualNode *> queue;

        queue.push(root);

        while (!queue.empty())
        {

            auto current_node = queue.front();
            queue.pop();
            if (current_node->left || current_node->right)
            {

                result += std::to_string(current_node->value) + ": ";
                if (current_node->left)
                {
                    queue.push(current_node->left);
                    result += std::to_string(current_node->left->value) + " ";
                }
                if (current_node->right)
                {
                    queue.push(current_node->right);

                    result += std::to_string(current_node->right->value) + " ";
                }
                result += '\n';
            }
        }
        return result;
    }

    void RedBlackTree::insert(IndividualNode *node)
    {
        std::lock_guard<std::mutex> lock(this->lock);
        this->root = binary_search_tree_insert(root, node);
        this->fixup(node);
        this->root->color = NodeColor::BLACK;
        this->num_nodes++;
    }

    void RedBlackTree::remove_smallest_node()
    {
        std::lock_guard<std::mutex> lock(this->lock);
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
        this->num_nodes--;
    }

    IndividualNode *RedBlackTree::get_largest_node()
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
    IndividualNode *RedBlackTree::get_random_node()
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

}