//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

Light::Light(){

}


Light::~Light(){

}

////////////////
// setAmbient //
////////////////

/**
 * this method allows to set the ambient value of a light
 * @param the ambient value
 * @return void
 */
void Light::setAmbient(glm::vec4 ambient){
    this->ambient = ambient;
}

////////////////
// setDiffuse //
////////////////

/**
 * this method allows to set the diffuse value of a light
 * @param the diffuse value
 * @return void
 */
void Light::setDiffuse(glm::vec4 diffuse){
    this->diffuse = diffuse;
}

/////////////////
// setSpecular //
/////////////////

/**
 * this method allows to set the specular value of a light
 * @param the specular value
 * @return void
 */
void Light::setSpecular(glm::vec4 specular){
    this->specular = specular;
}

/////////////////
// setPosition //
/////////////////

/**
 * this method allows to set the position value of a light
 * @param the position value
 * @return void
 */
void Light::setPosition(glm::vec4 position) {
    this->position = position;
}

//////////////////
// setShininess //
//////////////////

/**
 * this method allows to set the shininess value of a light
 * @param the shininess value
 * @return void
 */
void Light::setShininess(int shininess){
    this->shininess = shininess;
}

///////////////
// setLightN //
///////////////

/**
 * this method allows to set the number of light
 * @param the number of light
 * @return void
 */
void Light::setLightN(int light_n){
    this->light_n = light_n;
}

///////////////
// setCutoff //
///////////////

/**
 * this method allows to set the cutoff value of a light
 * @param the cutoff value
 * @return void
 */
void Light::setCutoff(float cutoff){
    this->cutoff = cutoff;
}

//////////////////
// setDirection //
//////////////////

/**
 * this method allows to set the direction value of a light
 * @param the direction value
 * @return void
 */
void Light::setDirection(glm::vec4 direction){
	this->direction = direction;
}

////////////////
// getAmbient //
////////////////

/**
 * this method allows to get the ambient value of a light
 * @param empty
 * @return the ambient value
 */
glm::vec4 Light::getAmbient(){
    return ambient;
}

////////////////
// getDiffuse //
////////////////

/**
 * this method allows to get the diffuse value of a light
 * @param empty
 * @return the diffuse value
 */
glm::vec4 Light::getDiffuse(){
    return diffuse;
}

/////////////////
// getSpecular //
/////////////////

/**
 * this method allows to get the specular value of a light
 * @param empty
 * @return the specular value
 */
glm::vec4 Light::getSpecular(){
    return specular;
}

/////////////////
// getPosition //
/////////////////

/**
 * this method allows to get the position of a light
 * @param empty
 * @return the position
 */
glm::vec4 Light::getPosition() {
    return position;
}

///////////////
// getCutoff //
///////////////

/**
 * this method allows to get the cutoff of a light
 * @param empty
 * @return the cutoff
 */
float Light::getCutoff(){
	return cutoff;
}

//////////////////
// getShininess //
//////////////////

/**
 * this method allows to get the shininess of a light
 * @param empty
 * @return the shininess
 */
int Light::getShininess(){
    return shininess;
}

///////////////
// getLightN //
///////////////

/**
 * this method allows to get the number of a light
 * @param empty
 * @return the number of a light
 */
int Light::getLightN(){
    return light_n;
}

//////////////////
// getDirection //
//////////////////

/**
 * this method allows to get the direction of a light
 * @param empty
 * @return the direction
 */
glm::vec4 Light::getDirection(){
	return this->direction;
}

////////////
// enable //
////////////

/**
 * this method allows to enable the current light with the number information
 * @param empty
 * @return void
 */
void Light::enable(){
    glEnable(GL_LIGHT0 + light_n);
}

/////////////
// disable //
/////////////

/**
 * this method allows to disable the current light with the number information
 * @param empty
 * @return void
 */
void Light::disable(){
    glDisable(GL_LIGHT0 + light_n);
}

///////////////
// setOption //
///////////////

/**
 * this method allows to set the option for render the light
 * @param empty
 * @return void
 */
void Light::setOption(){
	glm::vec4 zero(0.0f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(zero));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(zero));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(zero));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(ambient));

	glutSolidSphere(0.05f, 40, 40);
	glm::vec4 pos(0.0f, 0.0f, 0.0f, 1.0f);
	glLightfv(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_POSITION, glm::value_ptr(pos));
	glLightfv(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_SPECULAR, glm::value_ptr(specular));
	glLightf(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_SHININESS, shininess);
	glLightfv(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_SPOT_DIRECTION, glm::value_ptr(direction));
	glLightf(static_cast<GLenum>(GL_LIGHT0 + light_n), GL_SPOT_CUTOFF, cutoff);
}

////////////
// render //
////////////

/**
 * this method allows to render the light
 * @param camera information
 * @return void
 */
void Light::render(void * data){
    Camera* camera = (Camera *) data;
    enable();
    glLoadMatrixf(glm::value_ptr(camera->getMatrix() * getRenderMatrix()));
	setOption();
}

///////////////////
// renderInverse //
///////////////////

/**
 * this method allows to render the light in mirror mode
 * @param camera information
 * @return void
 */
void Light::renderInverse(void * data){
	Camera* camera = (Camera *)data;
	enable();
	glm::mat4 s = glm::scale(glm::mat4(1), glm::vec3(1, -1, 1));
	glLoadMatrixf(glm::value_ptr(camera->getMatrix() * s* getRenderMatrix()));
	setOption();
}
