//////////////
// #INCLUDE //
//////////////  

#include <iostream>
#include "Engine.h"

Camera::Camera(){
    near_plane = 1.0f;
    far_plane = 100.0f;
    fov = 45.0f;
}

///////////////
// setSWidth //
///////////////

/**
 * this method allows to set the screen width
 * @param the screen width
 * @return void
 */
void Camera::setSWidth(int s_width){
    this->s_width = s_width;
}

////////////////
// setSHeight //
////////////////

/**
 * this method allows to set the screen height
 * @param the screen height
 * @return void
 */
void Camera::setSHeight(int s_height){
    this->s_height = s_height;
}

//////////////////
// setNearPlane //
//////////////////

/**
 * this method allows to set the near plane value
 * @param the near plane value
 * @return void
 */
void Camera::setNearPlane(float near_plane){
    this->near_plane = near_plane;
}

/////////////////
// setFarPlane //
/////////////////

/**
 * this method allows to set the far plane  value
 * @param the far plane  value
 * @return void
 */
void Camera::setFarPlane(float far_plane){
    this->far_plane = far_plane;
}

////////////
// setFOV //
////////////

/**
 * this method allows to set the field of view value
 * @param the field of view value
 * @return void
 */
void Camera::setFOV(float fov){
    this->fov = fov;
}

/////////////////
// setPosition //
/////////////////

/**
 * this method allows to set the position
 * @param the position value
 * @return void
 */
void Camera::setPosition(glm::vec3 position){
    this->position = position;
}

//////////////////
// setDirection //
//////////////////

/**
 * this method allows to set the direction
 * @param the direction value
 * @return void
 */
void Camera::setDirection(glm::vec3 direction){
    this->direction = direction;
}

/////////////////
// setRotation //
/////////////////

/**
 * this method allows to set the rotation
 * @param the rotation value
 * @return void
 */
void Camera::setRotation(glm::vec3 rotation){
    this->rotation = rotation;
}

///////////
// setUp //
///////////

/**
 * this method allows to set the up value view
 * @param the up value
 * @return void
 */
void Camera::setUp(glm::vec3 cameraUp)
{
	this->cameraUp = cameraUp;
}

///////////////
// getSWidth //
///////////////

/**
 * this method allows to get the screen width
 * @param empty
 * @return the screen width
 */
int Camera::getSWidth(){
    return s_width;
}

////////////////
// getSHeight //
////////////////

/**
 * this method allows to get the screen height
 * @param empty
 * @return the screen height
 */
int Camera::getSHeight(){
    return s_height;
}

//////////////////
// getNearPlane //
//////////////////

/**
 * this method allows to get the near plane
 * @param empty
 * @return the near plane
 */
float Camera::getNearPlane(){
    return near_plane;
}

/////////////////
// getFarPlane //
/////////////////

/**
 * this method allows to get the far plane
 * @param empty
 * @return the far plane
 */
float Camera::getFarPlane(){
    return far_plane;
}

////////////
// getFOV //
////////////

/**
 * this method allows to get the field of view
 * @param empty
 * @return the field of view
 */
float Camera::getFOV(){
    return fov;
}

//////////////
// getSpeed //
//////////////

/**
 * this method allows to get the speed of the camera
 * @param empty
 * @return the speed of the camera
 */
float Camera::getSpeed(){
    return camera_speed;
}

////////////////////
// getMotionSpeed //
////////////////////

/**
 * this method allows to get the motion speed of the camera
 * @param empty
 * @return the motion speed of the camera
 */
float Camera::getMotionSpeed() {
    return camera_motion_speed;
}

/////////////////
// getPosition //
/////////////////

/**
 * this method allows to get the position
 * @param empty
 * @return the position
 */
glm::vec3 Camera::getPosition(){
    return position;
}

//////////////////
// getDirection //
//////////////////

/**
 * this method allows to get the direction
 * @param empty
 * @return the direction
 */
glm::vec3 Camera::getDirection(){
    return direction;
}

/////////////////
// getRotation //
/////////////////

/**
 * this method allows to get the rotation
 * @param empty
 * @return the rotation
 */
glm::vec3 Camera::getRotation(){
    return rotation;
}

///////////
// getUp //
///////////

/**
 * this method allows to get the up view
 * @param empty
 * @return the up view
 */
glm::vec3 Camera::getUp(){
    return cameraUp;
}

//////////////////////
// getInverseMatrix //
//////////////////////

/**
 * this method allows to get the inverse matrix of the camera
 * @param empty
 * @return the inverse matrix
 */
glm::mat4 Camera::getInverseMatrix(){
    return glm::inverse(getMatrix());
}

/////////////////////////
// getProjectionMatrix //
/////////////////////////

/**
 * this method allows to get the projection matrix of the camera
 * @param empty
 * @return the projection matrix
 */
glm::mat4 Camera::getProjectionMatrix(){
    return glm::perspective(glm::radians(fov), (float)s_width / (float) s_height, near_plane, far_plane);
}

//////////////
// setSpeed //
//////////////

/**
 * this method allows to set the camera speed
 * @param the speed value
 * @return void
 */
void Camera::setSpeed(float camera_speed){
	this->camera_speed = camera_speed;
}

////////////////////
// setMotionSpeed //
////////////////////

/**
 * this method allows to set the camera motion speed
 * @param the motion speed value
 * @return void
 */
void Camera::setMotionSpeed(float camera_motion_speed){
	this->camera_motion_speed = camera_motion_speed;
}

///////////////////////////
// getOrthographicMatrix //
///////////////////////////

/**
 * this method allows to get the Orthographic matrix of the camera
 * @param empty
 * @return the Orthographic matrix
 */
glm::mat4 Camera::getOrthographicMatrix(){
	return glm::ortho(0, s_width, 0, s_height,-1,1);
}

//////////////////
// updateMatrix //
//////////////////

/**
 * this method allows to update the camera in in the new position
 * @param empty
 * @return void
 */
void Camera::updateMatrix(){
    setMatrix(glm::lookAt(position, position + direction, cameraUp));
}

Camera::~Camera(){

}

////////////
// render //
////////////

/**
 * this method allows to render
 * @param camera data
 * @return void
 */
void Camera::render(void * data) {
    Node::render();
}

//////////////////////////
// correctIfOutOfBounds //
//////////////////////////

/**
 * this method allows to find the bounds of the scene
 * @param the value bounds of the scene
 * @return void
 */
void Camera::correctIfOutOfBounds(glm::vec4 out_of_bounds) {
	glm::vec3 pos = position;
	if (position.y < out_of_bounds.w) {
		position.y = out_of_bounds.w;
	}
	if (position.y > out_of_bounds.y) {
		position.y = out_of_bounds.y;
	}
	if (position.x > out_of_bounds.x) {
		position.x = out_of_bounds.x;
	}
	if (position.x < -out_of_bounds.x) {
		position.x = -out_of_bounds.x;
	}
	if (position.z > out_of_bounds.z) {
		position.z = out_of_bounds.z;
	}
	if (position.z < -out_of_bounds.z) {
		position.z = -out_of_bounds.z;
	}
}