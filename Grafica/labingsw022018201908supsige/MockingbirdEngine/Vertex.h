#pragma once
#include <glm/glm.hpp>

#include "LibApi.h"
class LIB_API Vertex{
    public:
        Vertex();
        Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v);
        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture_coords);
        ~Vertex();

        void setPosition(glm::vec3 position);
        void setNormal(glm::vec3 normal);
        void setTextureCoords(glm::vec2 texture_coords);
        glm::vec3 getPosition();
        glm::vec3 getNormal();
        glm::vec2 getTextureCoords();
    private:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture_coords;
};
