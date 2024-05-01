#include "gtest/gtest.h"
#include "evolution/population/red_black_tree.h"

#include "iostream"

#define create_node(val) tmp_node= new RedBlackTree::IndividualNode<int>(); tmp_node->value = val;
class RedBlackTreeTest : public ::testing::Test
{
protected:
    RedBlackTree::RedBlackTree<int> *tree;
    RedBlackTree::IndividualNode<int> *tmp_node;

    void SetUp() override
    {
        tree = new RedBlackTree::RedBlackTree<int>();
    }

    void TearDown() override
    {
        delete tree;
    }

    void checkRedNodeNotHaveRedChild(RedBlackTree::IndividualNode<int> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        checkRedNodeNotHaveRedChild(node->left);

        // check
        if (node->color == RedBlackTree::NodeColor::RED)
        {
            ASSERT_TRUE(node->left == nullptr || node->left->color == RedBlackTree::NodeColor::BLACK);
            ASSERT_TRUE(node->right == nullptr || node->right->color == RedBlackTree::NodeColor::BLACK);
        }

        checkRedNodeNotHaveRedChild(node->right);
    }
};

TEST_F(RedBlackTreeTest, InsertTest)
{

    for (int i = 0; i < 50; ++i){
        int randomValue = rand() % 100;
        create_node(randomValue);
        tree->insert(tmp_node);
        std::cout<<"Step"<< i<<":\n"<<tree->bfsPrint();
        checkRedNodeNotHaveRedChild(tree->root);
    }
}
