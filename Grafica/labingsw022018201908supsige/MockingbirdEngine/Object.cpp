//////////////
// #INCLUDE //
//////////////  

#include "Engine.h"

int Object::autoId = 0;

///////////
// getId //
///////////

/**
 * this method allows to get the current Id
 * @param empty
 * @return the id
 */
int Object::getId() {
	return id;
}

/////////////
// getName //
/////////////

/**
 * this method allows to get the current name
 * @param empty
 * @return the name
 */
string Object::getName() {
	return name;
}

/////////////
// getType //
/////////////

/**
 * this method allows to get the current type of the object
 * @param empty
 * @return the typename
 */
string Object::getType(){
	return this->type;
}

/////////////
// setName //
/////////////

/**
 * this method allows to set the current Id
 * @param the name value
 * @return void
 */
void Object::setName(string name) {
	this->name = name;
}

/////////////
// setType //
/////////////

/**
 * this method allows to set the type of the object
 * @param the type value
 * @return void
 */
void Object::setType(string type){
	this->type = type;
}

Object::Object() {
	this->setId();
}

Object::Object(string name) {
    this->name = name;
}

Object::~Object() {
}

///////////
// setId //
///////////

/**
 * this method allows to set the id of the object
 * @param empty
 * @return void
 */
void Object::setId(){
	id = autoId++;
}

////////////
// render //
////////////

/**
 * this method allows to render an object
 * @param the camera information
 * @return void
 */
void Object::render(void * data){

}

