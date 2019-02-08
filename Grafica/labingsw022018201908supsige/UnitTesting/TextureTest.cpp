#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"
#include <math.h>  

class TextureTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TextureTest() {
		// You can do set-up work for each test here.
	}

	~TextureTest() override {
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
	Texture texture;
};

TEST_F(TextureTest, TextureTest_texture_loadTextureFromFile_Test) {
	texture.loadTextureFromFile("../../scene/textures/gold.dds");
	EXPECT_NE(0, texture.getWidth());
	EXPECT_NE(0, texture.getHeight());
}



