#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"

class ObjectTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	ObjectTest() {
		// You can do set-up work for each test here.
	}

	~ObjectTest() override {
		// You can do clean-up work that doesn't throw exceptions here.
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
	Node obj0{ "name" };
	Node obj1{};
	Node obj2{};
};

TEST_F(ObjectTest, ObjectTest_object_AutoincrementId_Test) {
	int currentId = obj0.getId();
	EXPECT_EQ(++currentId, obj1.getId());
	EXPECT_EQ(++currentId, obj2.getId());
}

TEST_F(ObjectTest, ObjectTest_object_creation_Test) {
	ASSERT_EQ("name", obj0.getName());
}

TEST_F(ObjectTest, ObjectTest_object_getAndSetName_Test) {
	obj0.setName("name");
	ASSERT_EQ("name",obj0.getName());
}

TEST_F(ObjectTest, ObjectTest_object_getAndSetType_Test) {
	obj0.setType("node");
	ASSERT_EQ("node", obj0.getType());
}


