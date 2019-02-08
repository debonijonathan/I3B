#include <gtest/gtest.h>
#include "../MockingbirdEngine/Engine.h"  

class CameraTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	CameraTest() {
		// You can do set-up work for each test here.
	}

	~CameraTest() override {
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
	Camera camera{};
};

TEST_F(CameraTest, CameraTest_camera_getAndSetCameraUp_Test) {
	camera.setUp(glm::vec3(0.0f, 10.0f, 1.0f));
	ASSERT_EQ(glm::vec3(0.0f, 10.0f, 1.0f), camera.getUp());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetRotation_Test) {
	camera.setRotation(glm::vec3(0.0f, 10.0f, 1.0f));
	ASSERT_EQ(glm::vec3(0.0f, 10.0f, 1.0f), camera.getRotation());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetPosition_Test) {
	camera.setPosition(glm::vec3(0.0f, 10.0f, 1.0f));
	ASSERT_EQ(glm::vec3(0.0f, 10.0f, 1.0f), camera.getPosition());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetDirection_Test) {
	camera.setDirection(glm::vec3(0.0f, 10.0f, 1.0f));
	ASSERT_EQ(glm::vec3(0.0f, 10.0f, 1.0f), camera.getDirection());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetFOV_Test) {
	camera.setFOV(10.0f);
	ASSERT_EQ(10.0f, camera.getFOV());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetNearPlane_Test) {
	camera.setNearPlane(10.0f);
	ASSERT_EQ(10.0f, camera.getNearPlane());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetFarPlane_Test) {
	camera.setFarPlane(10.0f);
	ASSERT_EQ(10.0f, camera.getFarPlane());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetCameraSpeed_Test) {
	camera.setSpeed(0.3f);
	ASSERT_EQ(0.3f, camera.getSpeed());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetCameraMotionSpeed_Test) {
	camera.setMotionSpeed(0.3f);
	ASSERT_EQ(0.3f, camera.getMotionSpeed());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetSHeight_Test) {
	camera.setSHeight(10);
	ASSERT_EQ(10, camera.getSHeight());
}

TEST_F(CameraTest, CameraTest_camera_getAndSetSWidth_Test) {
	camera.setSWidth(10);
	ASSERT_EQ(10, camera.getSWidth());
}

TEST_F(CameraTest, CameraTest_camera_getAndInverseMatrix_Test) {
	ASSERT_EQ(glm::inverse(camera.getMatrix()), camera.getInverseMatrix());
}

TEST_F(CameraTest, CameraTest_camera_getProjectionMatrix_Test) {
	glm::mat4 perspective = glm::perspective(glm::radians(camera.getFOV()), (float)camera.getSWidth() / (float)camera.getSHeight(), camera.getNearPlane(), camera.getFarPlane());
	ASSERT_EQ(perspective , camera.getProjectionMatrix());
}

TEST_F(CameraTest, CameraTest_camera_getOrthographicMatrix_Test) {
	glm::mat4 orthographic = glm::ortho(0, camera.getSWidth(), 0, camera.getSHeight(), -1, 1);
	ASSERT_EQ(orthographic, camera.getOrthographicMatrix());
}

TEST_F(CameraTest, CameraTest_camera_creation_Test) {
	EXPECT_EQ(1.0f, camera.getNearPlane());
	EXPECT_EQ(100.0f, camera.getFarPlane());
	EXPECT_EQ(45.0f, camera.getFOV());
}
