#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"

class NodeTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	NodeTest() {
		// You can do set-up work for each test here.
		node_ptr0 = new Node();
		node_ptr1 = new Node();
	}

	~NodeTest() override {
		// You can do clean-up work that doesn't throw exceptions here.
		free(node_ptr0);
		free(node_ptr1);
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	void SetUp() override {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	void TearDown() override {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Foo.
	Node node0{ "name" };
	Node node1{};
	Node* node_ptr0;
	Node* node_ptr1;
};

TEST_F(NodeTest, NodeTest_node_creation_Test) {
	ASSERT_EQ("name", node0.getName());
}

TEST_F(NodeTest, NodeTest_node_getAndSetMatrix_Test) {
	node1.setMatrix(glm::mat4{ 1 });
	EXPECT_EQ(glm::mat4{ 1 }, node1.getMatrix());
	node1.setMatrix(glm::mat4{});
	EXPECT_EQ(glm::mat4{}, node1.getMatrix());
}

TEST_F(NodeTest, NodeTest_node_getAndSetParent_Test) {
	node1.setParent(node_ptr0);
	EXPECT_EQ(node_ptr0, node1.getParent());
	node1.setParent(node_ptr1);
	EXPECT_EQ(node_ptr1, node1.getParent());
}

TEST_F(NodeTest, NodeTest_node_addChild_Test) {
	node1.addChild(node_ptr0);
	node1.addChild(node_ptr1);
	EXPECT_EQ(&node1, node_ptr0->getParent());
	EXPECT_EQ(&node1, node_ptr1->getParent());
}

TEST_F(NodeTest, NodeTest_node_removeChild_Test) {
	int currentNOC = node1.getNumberOfChildren();
	int childCounter = currentNOC;

	for (int i = 0; i < currentNOC; i++) {
		node1.removeChild(0);
		EXPECT_EQ(childCounter--, node1.getNumberOfChildren());
	}
	ASSERT_EQ(0, node1.getNumberOfChildren());
}

TEST_F(NodeTest, NodeTest_node_getNumberOfChildren_Test) {
	EXPECT_EQ(0, node1.getNumberOfChildren());
	node1.addChild(node_ptr0);
	node1.addChild(node_ptr1);
	EXPECT_NE(0, node1.getNumberOfChildren());
}

TEST_F(NodeTest, NodeTest_node_removeAllChildren_Test) {
	node1.removeAllChildren();
	ASSERT_EQ(0, node1.getNumberOfChildren());
}



