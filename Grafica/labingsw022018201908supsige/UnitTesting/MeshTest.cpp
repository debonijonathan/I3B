#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"

class MeshTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	MeshTest() {
		// You can do set-up work for each test here.
		material = new Material();
	}

	~MeshTest() override {
		// You can do clean-up work that doesn't throw exceptions here.
		free(material);
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
	Material* material;
	Vertex vertex0;
	Vertex vertex1;
	Mesh mesh;
};

TEST_F(MeshTest, MeshTest_mesh_getAndSetMaterial_Test) {
	mesh.setMaterial(material);
	ASSERT_EQ(material->getId(), mesh.getMaterial()->getId());
}

TEST_F(MeshTest, MeshTest_mesh_addVertex_Test) {
	EXPECT_EQ(0, mesh.getNumberOfVertices());
	mesh.addVertex(vertex0);
	EXPECT_EQ(1, mesh.getNumberOfVertices());
}

TEST_F(MeshTest, MeshTest_mesh_getNumberOfVertices_Test) {
	EXPECT_EQ(0, mesh.getNumberOfVertices());
	mesh.addVertex(vertex0);
	EXPECT_EQ(1, mesh.getNumberOfVertices());
	mesh.addVertex(vertex1);
	EXPECT_EQ(2, mesh.getNumberOfVertices());
}



