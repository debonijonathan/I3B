#pragma once
#include "glm/glm.hpp"

#include "LibApi.h"
class LIB_API Material : public Object{
    public:
        Material();
        virtual ~Material();
        void setAmbient(glm::vec4 ambient);
        void setDiffuse(glm::vec4 diffuse);
        void setSpecular(glm::vec4 specular);
        void setShininess(int shininess);
        void setTexture(Texture* texture);
		void setTransparency(float alphaValue);

		bool isTransparent();
        glm::vec4 getAmbient();
        glm::vec4 getDiffuse();
        glm::vec4 getSpecular();
        int getShininess();
        Texture* getTexture();
        void render(void * data = nullptr);

    private:
        Texture *texture = nullptr;
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        int shininess;
};

