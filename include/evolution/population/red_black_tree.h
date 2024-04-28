#ifndef SYMMFEA_RED_BLACK_TREE_H
#define SYMMFEA_RED_BLACK_TREE_H
// #include "evolution/population/individual.h"
#include <iostream>
#include <queue>
enum class NodeColor
{
    RED,
    BLACK
};

struct Node
{

    float value;
    Node *parent;
    Node *left;
    Node *right;
    NodeColor color;
    
    Node(float value) : value(value), parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
};

Node *successor(Node *node)
{
    if (node->right != nullptr)
    {
        // If the node has a right child, find the leftmost node in the right subtree
        Node *current = node->right;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
    else
    {
        // If the node does not have a right child, find the first ancestor that is a left child
        Node *parent = node->parent;
        while (parent != nullptr && node == parent->right)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

// function to perform BST insertion of a Node
Node *bst(Node *trav,
          Node *temp)
{
    // If the tree is empty,
    // return a new Node
    if (!trav)
        return temp;

    // Otherwise recur down the tree
    if (temp->value < trav->value)
    {
        trav->left = bst(trav->left, temp);
        trav->left->parent = trav;
    }
    else if (temp->value > trav->value)
    {
        trav->right = bst(trav->right, temp);
        trav->right->parent = trav;
    }

    // Return the (unchanged) Node pointer
    return trav;
}

class RedBlackTree
{
private:
    Node *root;

    // Function performing right rotation
    // of the passed Node
    void rightrotate(Node *temp)
    {
        Node *left = temp->left;
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
    void leftrotate(Node *temp)
    {
        Node *right = temp->right;
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
    void fixup(Node *pt)
    {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

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

                Node *uncle_pt = grand_parent_pt->right;

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
                Node *uncle_pt = grand_parent_pt->left;

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
    void bfsPrint()
    {

        std::queue<Node *> queue;

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
    void insert(Node *node)
    {
        root = bst(root, node);
        fixup(node);
        root->color = NodeColor::BLACK;
    }

    // Function to remove a node from the Red-Black Tree
    void remove(Node *node)
    {
        //Case 1: If the node has two children
        if (node->left && node->right){
            Node *s = successor(node);
            
        }
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

#endif // SYMMFEA_RED_BLACK_TREE_H
