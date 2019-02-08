//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <iostream>
#include <math.h>

////////////
// render //
////////////

/**
 * this method allows all lists to be rendered
 * @param data contains the camera data
 * @return void
 */
void LIB_API List::render(void * data){
    Camera* camera = (Camera *) data;
    camera->updateMatrix();
	int cnt = 0;

	for (auto it : lights) {
		it->setLightN(cnt);
		it->render(camera);
		cnt++;
	}

	if (mirrorTrue == true) {
		for (auto it : list) {
			if(!(dynamic_cast<Mesh*>(it))->getMaterial()->isTransparent())
				dynamic_cast<Mesh*>(it)->renderInverse(camera);
		}

		for (auto it : lights) {
			it->setLightN(cnt);
			it->renderInverse(camera);
			cnt++;
		}
	}

	for (auto it : list) {
		if ((static_cast<Mesh*>(it))->getMaterial()->isTransparent()){
			it->render(camera);
		}
	}

	for (auto it : list) {
		if (!(static_cast<Mesh*>(it))->getMaterial()->isTransparent()){
			it->render(camera);
		}
	}
}

///////////////////
// compareMatrix //
///////////////////

/**
 * this method allows to find the distance between two matrices
 * @param obj0 and obj1 are the two objects containing the information of matrices
 * @return bool which is closer
 */
bool compareMatrix(Object* obj0, Object* obj1){
	glm::mat4 m0 = Engine::getEngine().getNodeByName(obj0->getName())->getMatrix();
	glm::mat4 m1 = Engine::getEngine().getNodeByName(obj1->getName())->getMatrix();
	glm::mat4 mc = Engine::camera.getMatrix();

	// calculation distance with the camera for obj0
	float d0 = sqrt(pow(mc[0][3]- m0[0][3],2)+pow(mc[1][3]- m0[1][3],2)+pow(mc[2][3]- m0[2][3],2));
	// calculation distance with the camera for obj1
	float d1 = sqrt(pow(mc[0][3] - m1[0][3], 2) + pow(mc[1][3] - m1[1][3], 2) + pow(mc[2][3] - m1[2][3], 2));

	return (d0 > d1);
}

//////////////////////////////
// renderTransparentObjects //
//////////////////////////////

void LIB_API List::renderTransparentObjects(void * data)
{
	Camera* camera = (Camera *)data;

	glDepthMask(GL_TRUE);

	//Depth - sort transparent objects(farthest to nearest).
	sort(transparentObjects.begin(), transparentObjects.end(), compareMatrix);

	for (auto it : transparentObjects) {
		it->render(data);
	}

	glDepthMask(GL_FALSE);
}

LIB_API List::List(){

}

List::~List(){
}

/////////
// add //
/////////

/**
 * this method allows you to add objects to the mesh and light lists
 * @param obj is the object to add to the list
 * @return void
 */
void List::add(Object* obj){
	Light* light = dynamic_cast<Light*>(obj);
	if (light != nullptr) {
		lights.push_back(light);
	}
	else {
		list.push_back(obj);
	}
}

////////////
// remove //
////////////

/**
 * this method allows you to remove objects from the mesh lists
 * @param n is the position to be removed
 * @return void
 */
void List::remove(int n){
    list.erase(list.begin() + n - 1);
}

/////////////////
// removeLight //
/////////////////

/**
 * this method allows you to remove objects from the light lists
 * @param n is the position to be removed
 * @return void
 */
void List::removeLight(int n){
    lights.erase(lights.begin() + n - 1);
}

///////////////
// removeAll //
///////////////

/**
 * this method allows you to remove all objects from the light and mesh lists
 * @param n is the position to be removed
 * @return void
 */
void List::removeAll(){
    list.clear();
	lights.clear();
}

///////////////
// setMirror //
///////////////

/**
 * this method allows you to set the display as a mirror
 * @param mirrorTrue matches the Boolean value 0 true and 1 false
 * @return void
 */
void List::setMirror(bool mirrorTrue){
	this->mirrorTrue = mirrorTrue;
}

///////////////
// getMirror //
///////////////

/**
 * this method allows you to get the status of mirror object
 * @param empty
 * @return the status of mirror
 */

bool List::getMirror() const{
	return mirrorTrue;
}

///////////////////////
// getNumberOfLights //
///////////////////////

/**
 * this method allows you to get the size of the light list 
 * @param empty
 * @return the size of the light list 
 */
int List::getNumberOfLights() const{
	return lights.size();
}

////////////////////////
// getNumberOfObjects //
////////////////////////

/**
 * this method allows you to get the size of the mesh list
 * @param empty
 * @return the size of the mesh list
 */
int List::getNumberOfObjects() const{
	return list.size();
}




