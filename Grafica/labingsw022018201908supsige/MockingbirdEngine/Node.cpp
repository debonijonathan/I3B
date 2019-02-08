//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"

Node::Node(){
}

Node::Node(string name){
    this->setName(name);
}

/////////////////
// getMatrix //
/////////////////

/**
 * This method allows to get the current matrix
 * @param empty
 * @return the current matrix
 */
glm::mat4 Node::getMatrix(){
    return matrix;
}

/////////////////
// setMatrix //
/////////////////

/**
 * This method allows to set the matrix in a node
 * @param the matrix 
 * @return void
 */
void Node::setMatrix(glm::mat4 matrix){
    this->matrix = matrix;
}

/////////////////////
// getRenderMatrix //
/////////////////////

/**
 * This method allows to get the final matrix of a tree
 * @param empty
 * @return matrix
 */
glm::mat4 Node::getRenderMatrix(){
    glm::mat4 finalMatrix;
    if(parent != nullptr){
        finalMatrix = parent->getRenderMatrix() * matrix;
        return finalMatrix;
    }
    return matrix;
}

/////////////////
//    render   //
/////////////////

/**
 * This method allows to render an object
 * @param camera data
 * @return void
 */
void Node::render(void * data){

}

/////////////////
//  setParent  //
/////////////////

/**
 * This method allows to set the father node
 * @param the father node
 * @return void
 */
void Node::setParent(Node* parent){
    this->parent = parent;
}

/////////////////
//  getParent  //
/////////////////

/**
 * This method allows to get the father node
 * @param empty
 * @return the father node
 */
Node* Node::getParent(){
    return parent;
}

///////////////////////
// recursiveResearch //
///////////////////////

/**
 * This method allows to get the node of a matrix by name
 * @param the name of a node
 * @return the node with the searched name
 */
Node* Node::recursiveResearch(string name){
    if(name.compare(getName()) == 0){
        return this;
    }

    for(auto child : children){
        Node* found = child->recursiveResearch(name);
        if(found != nullptr){
            return found;
        }
    }

    return nullptr;
}

/////////////////
//   addChild  //
/////////////////

/**
 * the method allows you to add child nodes
 * @param the child node
 * @return void
 */
void Node::addChild(Node* child){
    children.push_back(child);
	child->setParent(this);
}

/////////////////
// removeChild //
/////////////////

/**
 * the method allows you to remove child nodes
 * @param the position of child node
 * @return void
 */
void Node::removeChild(int n){
    children.erase(children.begin() + n);
}

///////////////////////
// removeAllChildren //
///////////////////////

/**
 * the method allows you to remove the children of a node
 * @param empty
 * @return void
 */
void Node::removeAllChildren(){
    children.clear();
}

/////////////////////////
// getNumberOfChildren //
/////////////////////////

/**
 * the method allows to obtain the number of children in a node
 * @param empty
 * @return the number of children
 */
unsigned int Node::getNumberOfChildren(){
	return children.size();
}

/////////////////
// getChildren //
/////////////////

/**
 * the method allows to obtain the children in a node
 * @param empty
 * @return children in a node
 */
vector<Node*> Node::getChildren(){
    return children;
}

Node::~Node(){
}
