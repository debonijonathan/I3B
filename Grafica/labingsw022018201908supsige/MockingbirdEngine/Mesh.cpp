//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


Mesh::Mesh(){

}


Mesh::~Mesh(){

}

/////////////////
// setMaterial //
/////////////////

/**
 * This method allows to set the material of a mesh
 * @param material contains the information about the material of the mesh
 * @return void
 */
void Mesh::setMaterial(Material* material){
    this->material = material;
}

/////////////////
// getMaterial //
/////////////////

/**
 * This method allows to obtain the material of a mesh
 * @param empty
 * @return the material of the mesh
 */
Material* Mesh::getMaterial(){
    return material;
}

///////////////
// addVertex //
///////////////

/**
 * This method allows to add a new vertex of a mesh
 * @param vertex contains the vertex of the mesh
 * @return void
 */
void Mesh::addVertex(Vertex vertex){
    vertices.push_back(vertex);
}

/////////////////////////
// getNumberOfVertices //
/////////////////////////

/**
 * This method allows to obtain the number of vertices of a mesh
 * @param empty
 * @return the number of the vertices
 */
int Mesh::getNumberOfVertices(){
	return vertices.size();
}

/////////////////
// renderStrip //
/////////////////

/**
 * this method allows rendering through the vertices
 * @param empty
 * @return void
 */

void Mesh::renderStrip(){
	glBegin(GL_TRIANGLES);
	for (auto vertex : vertices) {
		glm::vec3 normal = vertex.getNormal();
		glNormal3f(normal[0], normal[1], normal[2]);

		glm::vec2 texture_coords = vertex.getTextureCoords();
		glTexCoord2f(texture_coords[0], texture_coords[1]);

		glm::vec3 position = vertex.getPosition();
		glVertex3f(position[0], position[1], position[2]);
	}
	glEnd();
}

///////////////////
// renderInverse //
///////////////////

/**
 * This method allows the rendering of mirror mesh
 * @param data is the camera object
 * @return void
 */
void Mesh::renderInverse(void * data){
	Camera* camera = (Camera *)data;
	material->render();
	glm::mat4 s = glm::scale(glm::mat4(1), glm::vec3(1, -1, 1));
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glLoadMatrixf(glm::value_ptr(camera->getMatrix() * s* getRenderMatrix()));
	//glDisable(GL_CULL_FACE);
	renderStrip();	
}

////////////
// render //
////////////

/**
 * This method allows the rendering of mesh
 * @param data is the camera object
 * @return void
 */
void Mesh::render(void * data){
    Camera* camera = (Camera *) data;
    material->render();
    glLoadMatrixf(glm::value_ptr(camera->getMatrix() * getRenderMatrix()));
	glFrontFace(GL_CCW);
	renderStrip();  
    glDisable(GL_TEXTURE_2D);
}
