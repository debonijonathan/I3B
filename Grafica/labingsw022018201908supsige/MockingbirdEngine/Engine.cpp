#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved){
	// Check use:
	switch (reason){
		///////////////////////////
	case DLL_PROCESS_ATTACH: //
		break;


		///////////////////////////
	case DLL_PROCESS_DETACH: //
		break;
	}

	// Done:
	return true;
}
#endif

//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

Engine Engine::instance;
List* Engine::listm = new List();
Camera Engine::camera = Camera();
Camera Engine::camera2 = Camera();
int Engine::windowId = 0;
bool Engine::wireframe = false;
bool Engine::fpsToggle = false;
bool Engine::originalCamera = true;
void (* Engine::specialCallback) (int, int, int) = nullptr;
void (* Engine::keyboardCallback) (unsigned char, int, int) = nullptr;
void (* Engine::mouseCallback) (int, int, int, int) = nullptr;
void (* Engine::motionCallback) (int, int) = nullptr;

//Frame counter
int frames = 0;
float fps = 0.0f;

/////////////////////
// loadAllElements //
/////////////////////

/**
 * this method load all the elements in the list (light/mesh) 
 * @param the root node
 * @return void
 */

void Engine::loadAllElements(Node *node) {
    vector<Node*> children = node->getChildren();

    if(root == nullptr)
        root = node;
	listm->getName();

    if(dynamic_cast<Mesh*>(node) != nullptr){
        Mesh* new_mesh = (Mesh*) node;
        Material *new_material = new Material();
		std::cout << "asd" << std::endl;
        new_material = new_mesh->getMaterial();
        listm->add(new_mesh);
    }

    if(dynamic_cast<Light*>(node) != nullptr){
        Light* new_light = (Light*) node;
		listm->add(new_light);
    }

    for(auto child : children){
        loadAllElements(child);
    }
}

//////////////////////
// loadGeometryFile //
//////////////////////

/**
 * this method load with the OvoReader the tree of the scene
 * @param the path of the file
 * @return void
 */
void Engine::loadGeometryFile(const char* filePath){
	Node* root = getFinalScene(filePath);
    loadAllElements(root);
}

///////////////
// setMirror //
///////////////

/**
 * this method allows you to have the reverse scene
 * @param flag for enable or disable the inverse
 * @return void
 */
void Engine::setMirror(bool flag){
	if (flag != true) {
		listm->setMirror(false);
	}
	else {
		listm->setMirror(true);
	}
}

/////////////
// getList //
/////////////

/**
 * this method allows to get the list of meshes
 * @param empty
 * @return the list of meshes
 */
List LIB_API *Engine::getList(){
	return listm;
}

Engine::Engine(){
}

///////////////
// getEngine //
///////////////

/**
 * this method allows to get the instance of Engine
 * @param empty
 * @return the list of meshes
 */
Engine & Engine::getEngine(){
	return instance;
}

Engine::~Engine(){

}

/////////////////////
// changeWireframe //
/////////////////////

/**
 * this method allows to enable/disable wireframe
 * @param empty
 * @return void
 */
void Engine::changeWireframe(){
    wireframe = !wireframe;
}

/////////////////////
// changeFpsToggle //
/////////////////////

/**
 * this method allows to enable/disable fps
 * @param empty
 * @return void
 */
void Engine::changeFpsToggle(){
	fpsToggle = !fpsToggle;
}

//////////////////
// changeCamera //
//////////////////

/**
 * this method allows to change camera static-dinamic
 * @param empty
 * @return void
 */
void Engine::changeCamera() {
	originalCamera = !originalCamera;
}

/////////////////////////
// setKeyboardCallback //
/////////////////////////

/**
* this method allows to set the keyboardCallback method
* @param the function keyboardCallback
* @return void
*/
void Engine::setKeyboardCallback(void (* keyboardCallback) (unsigned char, int, int)){
    this->keyboardCallback = keyboardCallback;
}

////////////////////////
// setSpecialCallback //
////////////////////////

/**
 * this method allows to set the specialCallback method
 * @param the function specialCallback
 * @return void
 */
void Engine::setSpecialCallback(void (* specialCallback) (int, int, int)){
    this->specialCallback = specialCallback;
}

//////////////////////
// setMouseCallback //
//////////////////////

/**
 * this method allows to set the mouseCallback method
 * @param the function mouseCallback
 * @return void
 */
void Engine::setMouseCallback(void (* mouseCallback) (int, int, int, int)){
    this->mouseCallback = mouseCallback;
}

///////////////////////
// setMotionCallback //
///////////////////////

/**
 * this method allows to set the setMotionCallback method
 * @param the function setMotionCallback
 * @return void
 */
void Engine::setMotionCallback(void (* motionCallback) (int, int)){
    this->motionCallback = motionCallback;
}

/////////////////////
// displayCallback //
/////////////////////

/**
 * this method allows to set what the user should see in the window
 * @param empty
 * @return void
 */
void Engine::displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// 3D:
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(camera.getProjectionMatrix()));
	glMatrixMode(GL_MODELVIEW);



    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
    }

	if(originalCamera)
		Engine::listm->render(&camera);
	else
		Engine::listm->render(&camera2);
	if (fpsToggle) {
		// 2D:
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(camera.getOrthographicMatrix()));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(glm::mat4(1.0)));

		glDisable(GL_LIGHTING);

		/*management of fps*/
		char text[64];
		glColor3f(1.0f, 1.0f, 1.0f);
		sprintf(text, "FPS: %.1f", fps);
		glRasterPos2f(1.0f, 1.0f);
		glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);

		glEnable(GL_LIGHTING);
	}

	// Inc. frames:
	frames++;

    glutPostWindowRedisplay(windowId);
    glutSwapBuffers();

}

///////////////////
// timerCallback //
///////////////////

/**
 * this method registers a timer callback to be triggered in a specified number of milliseconds.
 * @param the value of the value parameter
 * @return void
 */
void Engine::timerCallback(int value){
	fps = frames / 1.0f;
	frames = 0;

	// Register the next update:
	glutTimerFunc(1000, timerCallback, 0);
}

//////////
// loop //
//////////

/**
 * this method enters the GLUT event processing loop.
 * @param empty
 * @return void
 */
void Engine::loop(){
    glutMainLoop();
}

/////////////////////
// reshapeCallback //
/////////////////////

/**
 * this method sets the reshape callback for the window.
 * @param the size of the window
 * @return void
 */
void Engine::reshapeCallback(int width, int height){
    glViewport(0, 0, width, height);
    camera.setSWidth(width);
    camera.setSHeight(height);
    camera.setFOV(45);
    camera.setNearPlane(0.1f);
    camera.setFarPlane(1000);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(camera.getProjectionMatrix()));
    glMatrixMode(GL_MODELVIEW);
    glutPostWindowRedisplay(windowId);
    glutSwapBuffers();
}

//////////
// init //
//////////

/**
 * this method set the properties for setting the initialized window
 * @param the argument passed by the main and the title of the window
 * @return void
 */
void Engine::init(int argc, char **argv, const char *title){
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);
	Engine::windowId = glutCreateWindow(title);
	option();
	glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
	glutTimerFunc(1000, timerCallback, 0);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Engine::camera.setPosition(glm::vec3(0.0f,0.1f,0.0f));
    Engine::camera.setDirection(glm::vec3(0.0f, 0.0f, -1.0f));
    Engine::camera.updateMatrix();

	Engine::camera2.setPosition(glm::vec3(0.0f, 45.0f, -40.0f));
	Engine::camera2.setDirection(glm::vec3(0.0f, 0.0f, 1.0f));
	Engine::camera2.updateMatrix();
}

///////////////////
// forwardCamera //
///////////////////

/**
 * this method change the forward position camera 
 * @param the vector with the limits of the camera position and if the limit is enable
 * @return void
 */
void Engine::forwardCamera(glm::vec4 out_of_bounds, bool flag){
    camera.setPosition(camera.getPosition() + camera.getDirection() * camera.getSpeed());
	if (flag == true) {
		camera.correctIfOutOfBounds(out_of_bounds);
	}
    Engine::camera.updateMatrix();
}

///////////////////
// backwardCamera //
///////////////////

/**
 * this method change the backward position camera
 * @param the vector with the limits of the camera position and if the limit is enable
 * @return void
 */
void Engine::backwardCamera(glm::vec4 out_of_bounds, bool flag){
    camera.setPosition(camera.getPosition() - camera.getDirection() * camera.getSpeed());
	if (flag == true) {
		camera.correctIfOutOfBounds(out_of_bounds);
	}
	Engine::camera.updateMatrix();
}

//////////////////
// toLeftCamera //
//////////////////

/**
 * this method change the Left position camera
 * @param the vector with the limits of the camera position and if the limit is enable
 * @return void
 */
void Engine::toLeftCamera(glm::vec4 out_of_bounds, bool flag){
    camera.setPosition(camera.getPosition() - glm::normalize(glm::cross(camera.getDirection(), camera.getUp())) * camera.getSpeed());
	if (flag == true) {
		camera.correctIfOutOfBounds(out_of_bounds);
	}
	Engine::camera.updateMatrix();
}

///////////////////
// toRightCamera //
///////////////////

/**
 * this method change the right position camera
 * @param the vector with the limits of the camera position and if the limit is enable
 * @return void
 */
void Engine::toRightCamera(glm::vec4 out_of_bounds, bool flag){
    camera.setPosition(camera.getPosition() + glm::normalize(glm::cross(camera.getDirection(), camera.getUp())) * camera.getSpeed());
	if (flag == true) {
		camera.correctIfOutOfBounds(out_of_bounds);
	}
	Engine::camera.updateMatrix();
}

////////////
// option //
////////////

/**
 * this method allows to set the option for the window
 * @param empty
 * @return void
 */
void Engine::option(){
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

//////////////////
// getWireframe //
//////////////////

/**
 * this method allows to get the wireframe status
 * @param empty
 * @return the status of wireframe
 */
bool Engine::getWireframe(){
	return wireframe;
}

///////////////////
// getFpsToggle //
///////////////////

/**
 * this method allows to get the fps status
 * @param empty
 * @return the status of fps
 */
bool Engine::getFpsToggle(){
	return fpsToggle;
}

///////////////////
// getNodeByName //
///////////////////

/**
 * this method allows to get the node by is name
 * @param the name of the node
 * @return the node with the name
 */
Node* Engine::getNodeByName(string name){
    return root->recursiveResearch(name);
}

//////////////////////
// setTrasformation //
//////////////////////

/**
 * this method allows to set a new matrix with a transformation
 * @param the node to be modified and the transformation matrix
 * @return void
 */
void Engine::setTrasformation(Node* node, glm::mat4 transformation) {
	node->setMatrix(node->getMatrix() * transformation);
}
