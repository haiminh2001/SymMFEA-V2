#include "gtest/gtest.h"
#include "evolution/population/red_black_tree.h"

class RedBlackTreeTest : public ::testing::Test {
protected:
    RedBlackTree::RedBlackTree<int> *tree;

    void SetUp() override {
        tree = new RedBlackTree::RedBlackTree<int>();
    }

    void TearDown() override {
        delete tree;
    }
};

TEST_F(RedBlackTreeTest, InsertTest) {
    

    RedBlackTree::IndividualNode<int>* node = new RedBlackTree::IndividualNode<int>(1);
    tree->insert(node);

    ASSERT_TRUE(tree->num_nodes == 1);
}

