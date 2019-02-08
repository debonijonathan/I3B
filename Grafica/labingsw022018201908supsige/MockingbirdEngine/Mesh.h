#pragma once
#include <glm/glm.hpp>

#include "LibApi.h"
class LIB_API Mesh : public Node
{
    public:
        Mesh();
        virtual ~Mesh();
        void render(void * data = nullptr);
        void setMaterial(Material* material);
        Material* getMaterial();
        void addVertex(Vertex vertex);
		int getNumberOfVertices();
		void renderInverse(void * data = nullptr);


    private:
		void renderStrip();
        Material* material;
        vector<Vertex> vertices;
};

