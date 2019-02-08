#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"

class ListTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	ListTest() {
		// You can do set-up work for each test here.
		node0 = new Node();
		node1 = new Node();
		light0 = new Light();
		light1 = new Light();
	}

	~ListTest() override {
		// You can do clean-up work that doesn't throw exceptions here.
		free(node0);
		free(node1);
		free(light0);
		free(light1);
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
	List list;
	Node* node0;
	Node* node1;
	Light* light0;
	Light* light1;
};

TEST_F(ListTest, ListTest_object_add_Test) {
	EXPECT_EQ(0, list.getNumberOfObjects());
	list.add(node0);
	EXPECT_EQ(1, list.getNumberOfObjects());
	list.add(node1);
	EXPECT_EQ(2, list.getNumberOfObjects());
}

TEST_F(ListTest, ListTest_object_remove_Test) {
	int currentNOO = list.getNumberOfObjects();
	int objectCounter = currentNOO;

	for (int i = 0; i < currentNOO; i++) {
		list.remove(0);
		EXPECT_EQ(objectCounter--, list.getNumberOfObjects());
	}
	ASSERT_EQ(0, list.getNumberOfObjects());
}

TEST_F(ListTest, ListTest_light_add_Test) {
	EXPECT_EQ(0, list.getNumberOfLights());
	list.add(light0);
	EXPECT_EQ(1, list.getNumberOfLights());
	list.add(light1);
	EXPECT_EQ(2, list.getNumberOfLights());
}

TEST_F(ListTest, ListTest_light_remove_Test) {
	int currentNOL = list.getNumberOfLights();
	int lightCounter = currentNOL;

	for (int i = 0; i < currentNOL; i++) {
		list.remove(0);
		EXPECT_EQ(lightCounter--, list.getNumberOfLights());
	}
	ASSERT_EQ(0, list.getNumberOfLights());
}

TEST_F(ListTest, ListTest_node_getNumberOfObjects_Test) {
	EXPECT_EQ(0, list.getNumberOfObjects());
	list.add(node0);
	list.add(node1);
	EXPECT_NE(0, list.getNumberOfObjects());
}

TEST_F(ListTest, ListTest_node_getNumberOfLights_Test) {
	EXPECT_EQ(0, list.getNumberOfLights());
	list.add(light0);
	list.add(light1);
	EXPECT_NE(0, list.getNumberOfLights());
}

TEST_F(ListTest, ListTest_list_removeAll_Test) {
	list.removeAll();
	ASSERT_EQ(0, list.getNumberOfObjects());
}

TEST_F(ListTest, ListTest_list_getAndSetMirrorTrue_Test) {
	list.setMirror(true);
	EXPECT_TRUE(list.getMirror());
	list.setMirror(false);
	EXPECT_FALSE(list.getMirror());
}


