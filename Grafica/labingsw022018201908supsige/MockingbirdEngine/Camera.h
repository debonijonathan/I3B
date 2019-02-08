#pragma once
#include "glm/gtc/matrix_transform.hpp"

#include "LibApi.h"
class LIB_API Camera : public Node {
    public:
        Camera();
        void setSWidth(int s_width);
        void setSHeight(int s_height);
        void setNearPlane(float near_plane);
        void setFarPlane(float far_plane);
        void setFOV(float fov);
        void setPosition(glm::vec3 position);
        void setDirection(glm::vec3 direction);
        void setRotation(glm::vec3 rotation);
		void setUp(glm::vec3 cameraUp);
		void correctIfOutOfBounds(glm::vec4 out_of_bounds);

        int getSWidth();
        int getSHeight();
        float getNearPlane();
        float getFarPlane();
        float getFOV();
		float getSpeed();
		float getMotionSpeed();
		glm::vec3 getPosition();
		glm::vec3 getDirection();
		glm::vec3 getRotation();
		glm::vec3 getUp();

        glm::mat4 getInverseMatrix();
		glm::mat4 getProjectionMatrix();
		void setSpeed(float camera_speed);
		void setMotionSpeed(float camera_motion_speed);
		glm::mat4 getOrthographicMatrix();
        void updateMatrix();
        ~Camera();
		void render(void * data = nullptr);
	private:
	    int s_width;
	    int s_height;
	    float camera_speed = 1.0f;
	    float camera_motion_speed = 0.2f;
	    float near_plane;
	    float far_plane;
	    float fov;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 rotation;
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

