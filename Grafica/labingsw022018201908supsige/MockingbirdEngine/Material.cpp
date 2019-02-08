//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
Material::Material(){
}


Material::~Material(){
}

////////////////
// setAmbient //
////////////////

/**
 * this method allows to set the ambient value of a Material
 * @param the ambient value
 * @return void
 */
void Material::setAmbient(glm::vec4 ambient){
    this->ambient = ambient;
}

////////////////
// setDiffuse //
////////////////

/**
 * this method allows to set the diffuse value of a Material
 * @param the diffuse value
 * @return void
 */
void Material::setDiffuse(glm::vec4 diffuse){
    this->diffuse = diffuse;
}

/////////////////
// setSpecular //
/////////////////

/**
 * this method allows to set the specular value of a Material
 * @param the specular value
 * @return void
 */
void Material::setSpecular(glm::vec4 specular){
    this->specular = specular;
}

////////////////
// setTexture //
////////////////

/**
 * this method allows to set the texture of a Material
 * @param the texture
 * @return void
 */
void Material::setTexture(Texture* texture){
    this->texture = texture;
}

/////////////////////
// setTransparency //
/////////////////////

/**
 * this method allows to set the alpha channel of ambient,
 * diffuse and specular vectors.
 * @param the texture
 * @return void
 */
void Material::setTransparency(float alphaValue){
	this->ambient.w = alphaValue;
	this->diffuse.w = alphaValue;
	this->specular.w = alphaValue;
}

///////////////////
// isTransparent //
///////////////////

/**
 * this method check if a material is trasparent 
 * @param empty
 * @return boolean value
 */
bool Material::isTransparent(){
	if((this->ambient.w != 1)&& (this->diffuse.w != 1)&& (this->specular.w != 1))
		return true;
	else return false;
}

//////////////////
// setShininess //
//////////////////

/**
 * this method allows to set the shininess value of a Material
 * @param the shininess value
 * @return void
 */
void Material::setShininess(int shininess){
    this->shininess = shininess;
}

////////////////
// getAmbient //
////////////////

/**
 * this method allows to get the ambient value of a Material
 * @param empty
 * @return the ambient value
 */
glm::vec4 Material::getAmbient(){
    return ambient;
}

////////////////
// getDiffuse //
////////////////

/**
 * this method allows to get the diffuse value of a Material
 * @param empty
 * @return the diffuse value
 */
glm::vec4 Material::getDiffuse(){
    return diffuse;
}

/////////////////
// getSpecular //
/////////////////

/**
 * this method allows to get the specular value of a Material
 * @param empty
 * @return the specular value
 */
glm::vec4 Material::getSpecular(){
    return specular;
}

//////////////////
// getShininess //
//////////////////

/**
 * this method allows to get the shininess value of a Material
 * @param empty
 * @return the shininess value
 */
int Material::getShininess(){
    return shininess;
}

////////////////
// getTexture //
////////////////

/**
 * this method allows to get the texture of a Material
 * @param empty
 * @return the texture
 */
Texture* Material::getTexture(){
    return texture;
}

////////////
// render //
////////////

/**
 * this method allows to render the Material
 * @param camera information
 * @return void
 */
void Material::render(void * data){
    if(texture != nullptr){
        texture->render();
    }

    glm::vec4 zero(0.0f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(zero));
}
