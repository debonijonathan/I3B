#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "LibApi.h"
class LIB_API Node : public Object{
    public:
        Node();
        Node(string name);
		virtual ~Node();

        glm::mat4 getMatrix();
        void setMatrix(glm::mat4 matrix);
        glm::mat4 getRenderMatrix();

        void setParent(Node* parent);
        Node* getParent();
        vector<Node*> getChildren();

        Node* recursiveResearch(string name);
        void render(void * data = nullptr);
        void addChild(Node* child);
        void removeChild(int n);
        void removeAllChildren();
        unsigned int getNumberOfChildren();
    private:
        glm::mat4 matrix = glm::mat4(1.0f);
        Node* parent = nullptr;
        vector<Node*> children;
};

