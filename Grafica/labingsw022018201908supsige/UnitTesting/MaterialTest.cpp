#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"
#include <math.h>  

class MaterialTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	MaterialTest() {
		// You can do set-up work for each test here.
		texture = new Texture();
	}

	~MaterialTest() override {
		// You can do clean-up work that doesn't throw exceptions here.
		free(texture);
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
	Material material;
	Texture* texture;
};

TEST_F(MaterialTest, MaterialTest_material_getAndSetShininess_Test) {
	for (int i = 0; i < 8; i++) {
		material.setShininess(pow(2, i));
		EXPECT_EQ(pow(2, i), material.getShininess());
	}
}

TEST_F(MaterialTest, MaterialTest_material_getAndSetDiffuse_Test) {
	material.setDiffuse(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), material.getDiffuse());
	material.setDiffuse(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), material.getDiffuse());
}

TEST_F(MaterialTest, MaterialTest_material_getAndSetAmbient_Test) {
	material.setAmbient(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), material.getAmbient());
	material.setAmbient(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), material.getAmbient());
}

TEST_F(MaterialTest, MaterialTest_material_getAndSetSpecular_Test) {
	material.setSpecular(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), material.getSpecular());
	material.setSpecular(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), material.getSpecular());
}

TEST_F(MaterialTest, MaterialTest_material_getAndSetTexture_Test) {
	material.setTexture(texture);
	ASSERT_EQ(texture, material.getTexture());
}

TEST_F(MaterialTest, MaterialTest_material_isTransparentAndSetTransparency_Test) {
	material.setTransparency(1);
	EXPECT_FALSE(material.isTransparent());
	material.setTransparency(0.5);
	EXPECT_TRUE(material.isTransparent());
}

