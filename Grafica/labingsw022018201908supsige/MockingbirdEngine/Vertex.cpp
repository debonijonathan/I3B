//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"


Vertex::Vertex(){

}

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v){
    position = glm::vec3(x, y, z);
    normal = glm::vec3(nx, ny, nz);
    texture_coords = glm::vec2(u,v);
}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture_coords){
    this->position = position;
    this->normal = normal;
    this->texture_coords = texture_coords;
}

/////////////////
// setPosition //
/////////////////

/**
 * this method allows to set the position
 * @param position of the triangle
 * @return void
 */
void Vertex::setPosition(glm::vec3 position){
    this->position = position;
}

///////////////
// setNormal //
///////////////

/**
 * this method allows to set the normal 
 * @param normal of the triangle
 * @return void
 */
void Vertex::setNormal(glm::vec3 normal){
    this->normal = normal;
}

//////////////////////
// setTextureCoords //
//////////////////////

/**
 * this method allows to set the texture coordinate
 * @param texture in 2d coordinate
 * @return void
 */
void Vertex::setTextureCoords(glm::vec2 texture_coords){
    this->texture_coords = texture_coords;
}

/////////////////
// getPosition //
/////////////////

/**
 * this method allows to get the current position
 * @param empty
 * @return position of the object
 */
glm::vec3 Vertex::getPosition(){
    return position;
}

///////////////
// getNormal //
///////////////

/**
 * this method allows to get the current normal
 * @param empty
 * @return normal of the triangle
 */
glm::vec3 Vertex::getNormal(){
    return normal;
}

//////////////////////
// getTextureCoords //
//////////////////////

/**
 * this method allows to get the current texture coordinate
 * @param empty
 * @return texture coordinate
 */
glm::vec2 Vertex::getTextureCoords(){
    return texture_coords;
}

Vertex::~Vertex(){

}
