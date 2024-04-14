#include "gtest/gtest.h"
#include "components/functions/node.h"
#include "central_units/individual_infos.h"
#include <Eigen/Dense>

using Eigen::ArrayXf;
using Eigen::ArrayXXf;

TEST(NodeTest, ConstructorTest) {
    Node node(2, 1);
    EXPECT_EQ(node.arity, 2);
    EXPECT_EQ(node.index, 1);
}

TEST(NodeTest, IsLeafTest) {
    Node leafNode(0);
    EXPECT_TRUE(leafNode.is_leaf());

    Node nonLeafNode(1);
    EXPECT_FALSE(nonLeafNode.is_leaf());
}

TEST(NodeTest, BackpropTest) {
    Node node(2, 1);
    ArrayXf dY = ArrayXf::Random(3);
    std::vector<ArrayXf> result = node.backprop(dY);
    // Add your own assertions based on what you expect the result to be
}

TEST(NodeTest, ForwardTest) {
    Node node(2, 1);
    ArrayXXf X = ArrayXXf::Random(3, 3);
    ArrayXf result = node.forward(X);
    // Add your own assertions based on what you expect the result to be
}

TEST(NodeTest, WeightTest) {
    Node node(2, 1);
    float weight = node.weight();
    // Add your own assertions based on what you expect the weight to be
}

TEST(NodeTest, MatrixVectorRowWiseProductionTest) {
    std::vector<ArrayXf> M = {ArrayXf::Random(3), ArrayXf::Random(3)};
    ArrayXf v = ArrayXf::Random(3);
    std::vector<ArrayXf> result = matrix_vector_row_wise_production(M, v);
    // Add your own assertions based on what you expect the result to be
}