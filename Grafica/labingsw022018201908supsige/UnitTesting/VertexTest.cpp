#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"

class VertexTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	VertexTest() {
		// You can do set-up work for each test here.
	}

	~VertexTest() override {
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
	glm::vec3 position = glm::vec3(1.0f, 0.5f, 1.5f);
	glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec2 texture_coords = glm::vec2(2.3f, 4.5f);

	Vertex vertex0{1.0f,0.5f,1.5f,0.0f,1.0f,0.0f,2.3f,4.5f};
	Vertex vertex1{position,normal,texture_coords};
};

TEST_F(VertexTest, VertexTest_vertex_creation_Test) {
	EXPECT_EQ(position, vertex0.getPosition());
	EXPECT_EQ(normal, vertex0.getNormal());
	EXPECT_EQ(texture_coords, vertex0.getTextureCoords());

	EXPECT_EQ(position, vertex1.getPosition());
	EXPECT_EQ(normal, vertex1.getNormal());
	EXPECT_EQ(texture_coords, vertex1.getTextureCoords());
}

TEST_F(VertexTest, VertexTest_vertex_getAndSetPosition_Test) {
	vertex0.setPosition(glm::vec3(0.0f));
	EXPECT_EQ(glm::vec3(0.0f), vertex0.getPosition());
	vertex0.setPosition(glm::vec3(3.0f, 2.5f, 7.5f));
	EXPECT_EQ(glm::vec3(3.0f, 2.5f, 7.5f), vertex0.getPosition());
}

TEST_F(VertexTest, VertexTest_vertex_getAndSetNormal_Test) {
	vertex0.setNormal(glm::vec3(0.0f));
	EXPECT_EQ(glm::vec3(0.0f), vertex0.getNormal());
	vertex0.setNormal(glm::vec3(1.0f, 1.0f, 0.0f));
	EXPECT_EQ(glm::vec3(1.0f, 1.0f, 0.0f), vertex0.getNormal());
}

TEST_F(VertexTest, VertexTest_vertex_getAndSetTextureCoords_Test) {
	vertex0.setTextureCoords(glm::vec2(0.0f));
	EXPECT_EQ(glm::vec2(0.0f), vertex0.getTextureCoords());
	vertex0.setTextureCoords(glm::vec2(4.5f, 5.0f));
	EXPECT_EQ(glm::vec2(4.5f, 5.0f), vertex0.getTextureCoords());
}
