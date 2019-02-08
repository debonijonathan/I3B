#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"
#include <math.h>  

class LightTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	LightTest() {
		// You can do set-up work for each test here.
	}

	~LightTest() override {
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
	Light light;
};

TEST_F(LightTest, LightTest_light_getAndSetDirection_Test) {
	light.setDirection(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), light.getDirection());
	light.setDirection(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), light.getDirection());
}

TEST_F(LightTest, LightTest_light_getAndSetPosition_Test) {
	light.setPosition(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), light.getPosition());
	light.setPosition(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), light.getPosition());
}

TEST_F(LightTest, LightTest_light_getAndSetLightN_Test) {
	for (int i = 0; i < 9; i++) {
		light.setLightN(i);
		EXPECT_EQ(i, light.getLightN());
	}
}

TEST_F(LightTest, LightTest_light_getAndSetShininess_Test) {
	for (int i = 0; i < 8; i++) {
		light.setShininess(pow(2,i));
		EXPECT_EQ(pow(2, i), light.getShininess());
	}
}

TEST_F(LightTest, LightTest_light_getAndSetAmbient_Test) {
	light.setAmbient(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), light.getAmbient());
	light.setAmbient(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), light.getAmbient());
}

TEST_F(LightTest, LightTest_light_getAndSetDiffuse_Test) {
	light.setDiffuse(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), light.getDiffuse());
	light.setDiffuse(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), light.getDiffuse());
}

TEST_F(LightTest, LightTest_light_getAndSetSpecular_Test) {
	light.setSpecular(glm::vec4(0));
	EXPECT_EQ(glm::vec4(0), light.getSpecular());
	light.setSpecular(glm::vec4(1.0, 1.0, 0.0, 1.0));
	EXPECT_EQ(glm::vec4(1.0, 1.0, 0.0, 1.0), light.getSpecular());
}

TEST_F(LightTest, LightTest_light_getAndSetCutoff_Test) {
	light.setCutoff(0.0f);
	EXPECT_EQ(0.0f, light.getCutoff());
	light.setCutoff(180.0f);
	EXPECT_EQ(180.0f, light.getCutoff());
}


