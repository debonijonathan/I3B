#pragma once

#include "LibApi.h"
class LIB_API Light : public Node{
    public:
        Light();
        virtual ~Light();
        void setAmbient(glm::vec4 ambient);
        void setDiffuse(glm::vec4 diffuse);
        void setSpecular(glm::vec4 specular);
        void setPosition(glm::vec4 position);
        void setShininess(int shininess);
        void setCutoff(float cutoff);
        void setLightN(int light_n);
		void setDirection(glm::vec4 direction);

        glm::vec4 getAmbient();
        glm::vec4 getDiffuse();
        glm::vec4 getSpecular();
        glm::vec4 getPosition();
		float getCutoff();
        int getShininess();
        int getLightN();
		glm::vec4 getDirection();
        void render(void * data = nullptr);
		void renderInverse(void * data = nullptr);
        void enable();
        void disable();

    private:
		void setOption();
        int light_n;
        int shininess;
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 position;
        float cutoff;
		glm::vec4 direction;
};

