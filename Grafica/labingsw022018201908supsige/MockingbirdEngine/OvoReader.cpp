#include "OvoReader.h"

/**
 * @file		ovoreader.cpp
 * @brief	Minimal decoder for the OverVision Object (OVO) 3D file format
 *
 * @author	Achille Peternier (achille.peternier@gmail.com), (C) 2013-2018
 */



 //////////////
 // #INCLUDE //
 //////////////  

	// GLM:
	//#define GLM_ENABLE_EXPERIMENTAL     // Silly requirement since 0.9.9
#define GLM_FORCE_CTOR_INIT         // Constructors no longer init to identity since 0.9.9
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>

// C/C++:
#include <iostream>
#include <iomanip>   
#include <limits.h>
#include <vector>
#include <map>
#include <stack>
#include "Material.h"
#include "Light.h"
#include "Mesh.h"
#include <sstream>      // std::stringstream


using namespace std;



/////////////
// #DEFINE //
/////////////

   // General:
#define APP_NAME "OVO Reader v0.7r"

// Macro for printing an OvMatrix4 to console:   
#define MAT2STR(m) std::cout << "   Matrix  . . . :  \t" << m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\t" << m[3][0] << std::endl \
                           << "                    \t" << m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\t" << m[3][1] << std::endl \
                           << "                    \t" << m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\t" << m[3][2] << std::endl \
                           << "                    \t" << m[0][3] << "\t" << m[1][3] << "\t" << m[2][3] << "\t" << m[3][3] << std::endl 

   // Stripped-down redefinition of OvObject (just for the chunk IDs):
class OvObject{
public:
	enum class Type : int { ///< Type of entities
		// Foundation types:
		OBJECT = 0,
		NODE,
		OBJECT2D,
		OBJECT3D,
		LIST,

		// Derived classes:
		BUFFER,
		SHADER,
		TEXTURE,
		FILTER,
		MATERIAL,
		FBO,
		QUAD,
		BOX,
		SKYBOX,
		FONT,
		CAMERA,
		LIGHT,
		BONE,
		MESH,	   // Keep them...
		SKINNED, // ...consecutive        
		INSTANCED,
		PIPELINE,
		EMITTER,

		// Animation type
		ANIM,

		// Physics related:
		PHYSICS,

		// Terminator:
		LAST,
	};
};

// Stripped-down redefinition of OvMesh (just for the subtypes):
class OvMesh{
public:
	enum class Subtype : int {///< Kind of mesh
	
		// Foundation types:
		DEFAULT = 0,
		NORMALMAPPED,
		TESSELLATED,

		// Terminator:
		LAST,
	};
};

// Stripped-down redefinition of OvLight (just for the subtypes):
class OvLight{
public:
	enum class Subtype : int {///< Kind of light
	
		// Foundation types:
		OMNI = 0,
		DIRECTIONAL,
		SPOT,

		// Terminator:
		LAST,
	};
};


//Struct where we save the node and the nr of children
struct Element {
	Node* node;
	unsigned int nr_element;
};

//////////
// tree //
//////////

/**
 * Method for parse all the elements and set the proper relationship  
 * @param elements all the elements parsed by OvoReader
 * @return void
 */
void tree(vector<Element*>& elements) {
	vector<Element*> myStack;
	for (int i = 0; i < elements.size(); i++) {
		if (elements.at(i)->nr_element == 0 && myStack.size() == 0) {
			//Root without Children
			return;
		}
		else if (elements.at(i)->nr_element != 0 && myStack.size() == 0) {
			//Root with Children
			myStack.push_back(elements.at(i));
		}
		else if (elements.at(i)->nr_element != 0 && myStack.size() != 0) {
			//The element have children but is not the root
			//so need to be save in the stack
			myStack.back()->nr_element -= 1;
			myStack.back()->node->addChild(elements.at(i)->node);
			myStack.push_back(elements.at(i));

		}
		else if(elements.at(i)->nr_element == 0 && myStack.size() != 0){
			//The element have not children, is a leaf
			//so need to be set the parent
			//and check if the father have other children otherwise need to be deleted
			//from the stack
			myStack.back()->nr_element -= 1;

			myStack.back()->node->addChild(elements.at(i)->node);
			while (myStack.back()->nr_element == 0 && myStack.size() != 1) {
					myStack.pop_back();

			}
			

		}
	}
	//Delete the root from the stack
	myStack.pop_back();
}

///////////////
// printTree //
///////////////

/**
 * print all the elements parsed by OvoReader with the correct relationship
 * @param elements all the elements parsed by OvoReader
 * @return void
 */
void printTree(vector<Element*>& obj){
	for (int i = 0; i < obj.size(); i++) {
		Element* root = obj.at(i);
		if (i != 0) {
			Mesh* m = dynamic_cast<Mesh*>(obj.at(i)->node);

			if (m != NULL) {
				Material* mat = m->getMaterial();
				if (mat != nullptr)
					cout << m->getMaterial()->getTexture()->getName() << " ";
			}
		}
		else {
			cout << obj.at(i)->node->getNumberOfChildren() << " " << obj.at(i)->node->getName() << endl;
		}
	}
}

///////////////////
// getFinalScene //
///////////////////

/**
 * Application entry point. For details on the file format, build and browse the Doxygen documentation from OvoReader.
 * @param filePath position of the file .ovo
 * @return the root node
 */
Node* getFinalScene(const char* filePath){
	vector<Element*> obj;
	map<string, Material*> materials;

	unsigned int children;

	// Check for options:
	bool verbose = false;

	// Open file:
	FILE *dat = fopen(filePath, "rb");
	if (dat == nullptr){
		std::cout << "ERROR: unable to open file '" << filePath << "'" << endl;
		return NULL;
	}

	// Configure stream:
	std::cout.precision(2);  // 2 decimals are enough
	std::cout << fixed;      // Avoid scientific notation

	//Insert the default Material
	Material* defaultMat = new Material();
	defaultMat->setAmbient(glm::vec4(1, 1, 1, 1));
	defaultMat->setDiffuse(glm::vec4(1, 1, 1, 1));
	defaultMat->setShininess(1);
	defaultMat->setSpecular(glm::vec4(1, 1, 1, 1));
	defaultMat->setName("[none]");
	materials.insert(std::make_pair(defaultMat->getName(), defaultMat));

	 /////////////////
	 // Parse chuncks:
	unsigned int chunkId, chunkSize;
	while (true){

		fread(&chunkId, sizeof(unsigned int), 1, dat);
		if (feof(dat))
			break;
		fread(&chunkSize, sizeof(unsigned int), 1, dat);


		// Load whole chunk into memory:
		char *data = new char[chunkSize];
		if (fread(data, sizeof(char), chunkSize, dat) != chunkSize){

			fclose(dat);
			delete[] data;
			return NULL;
		}

		// Parse chunk information according to its type:
		unsigned int position = 0;
		switch ((OvObject::Type) chunkId){
			///////////////////////////////
		case OvObject::Type::OBJECT: {

			// OVO revision number:
			unsigned int versionId;
			memcpy(&versionId, data + position, sizeof(unsigned int));

			position += sizeof(unsigned int);
		}
		break;

		/////////////////////////////
		case OvObject::Type::NODE: {
			Node* node = new Node();
			char nodeName[FILENAME_MAX];
			strcpy(nodeName, data + position);

			position += (unsigned int)strlen(nodeName) + 1;

			// Node matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			//if (verbose)
			//	MAT2STR(matrix);
			position += sizeof(glm::mat4);

			// Nr. of children nodes:
			memcpy(&children, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// Optional target node, [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy(targetName, data + position);

			position += (unsigned int)strlen(targetName) + 1;

			node->setName(nodeName);
			node->setMatrix(matrix);
			node->setType("node");
			obj.push_back(new Element{node, children});
		}
		break;


		/////////////////////////////////
		case OvObject::Type::MATERIAL: {
			Material* material = new Material();
			Texture* texture = new Texture();
			// Material name:
			char materialName[FILENAME_MAX];
			strcpy(materialName, data + position);

			material->setName(materialName);
			position += (unsigned int)strlen(materialName) + 1;

			// Material term colors, starting with emissive:
			glm::vec3 emission, albedo;
			memcpy(&emission, data + position, sizeof(glm::vec3));
			position += sizeof(glm::vec3);

			// Albedo:

			memcpy(&albedo, data + position, sizeof(glm::vec3));
			// conversion into phong:
			glm::vec4 ambient(albedo.r * 0.2, albedo.g * 0.2, albedo.b*0.2, 1);
			glm::vec4 specular(albedo.r * 0.4, albedo.g * 0.4, albedo.b*0.4, 1);
			glm::vec4 diffuse(albedo.r * 0.6, albedo.g * 0.6, albedo.b*0.6, 1);

			material->setAmbient(ambient);
			material->setSpecular(specular);
			material->setDiffuse(diffuse);
			position += sizeof(glm::vec3);

			// Roughness factor:
			float roughness;
			memcpy(&roughness, data + position, sizeof(float));
			position += sizeof(float);
			// Conversion Shininess:
			material->setShininess((1 - glm::sqrt(roughness))*128);

			// Metalness factor:
			float metalness;
			memcpy(&metalness, data + position, sizeof(float));
			position += sizeof(float);

			// Transparency factor:
			float alpha;
			memcpy(&alpha, data + position, sizeof(float));
			//aggiungo setTrasp
			material->setTransparency(alpha);
			position += sizeof(float);

			// Albedo texture filename, or [none] if not used:
			char textureName[FILENAME_MAX];
			strcpy(textureName, data + position);
			texture->setName(textureName);
			texture->setType("texture");
			stringstream ss;
			ss << "scene/textures/";
			ss << textureName;
			string str = ss.str();
            const char* cstr = str.c_str();
			if(std::string(textureName) != "[none]") {
				texture->loadTextureFromFile(cstr);
			}
			material->setTexture(texture);
			position += (unsigned int)strlen(textureName) + 1;

			// Normal map filename, or [none] if not used:
			char normalMapName[FILENAME_MAX];
			strcpy(normalMapName, data + position);
			position += (unsigned int)strlen(normalMapName) + 1;

			// Height map filename, or [none] if not used:
			char heightMapName[FILENAME_MAX];
			strcpy(heightMapName, data + position);
			position += (unsigned int)strlen(heightMapName) + 1;

			// Roughness map filename, or [none] if not used:
			char roughnessMapName[FILENAME_MAX];
			strcpy(roughnessMapName, data + position);
			position += (unsigned int)strlen(roughnessMapName) + 1;

			// Metalness map filename, or [none] if not used:
			char metalnessMapName[FILENAME_MAX];
			strcpy(metalnessMapName, data + position);
			position += (unsigned int)strlen(metalnessMapName) + 1;
			material->setType("material");


			// Insert the material in a map with the name for the key
			materials.insert(std::make_pair(materialName,material));
		}
		break;


		////////////////////////////////
		case OvObject::Type::MESH:    //
		case OvObject::Type::SKINNED:{
			Mesh* mesh = new Mesh();
			// Both standard and skinned meshes are handled through this case:
			bool isSkinned = false;
			if ((OvObject::Type) chunkId == OvObject::Type::SKINNED){
				isSkinned = true;
			}


			// Mesh name:
			char meshName[FILENAME_MAX];
			strcpy(meshName, data + position);
			position += (unsigned int)strlen(meshName) + 1;


			// Mesh matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			//if (verbose)
			//	MAT2STR(matrix);
			position += sizeof(glm::mat4);

			// Mesh nr. of children nodes:
			memcpy(&children, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// Optional target node, or [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy(targetName, data + position);
			position += (unsigned int)strlen(targetName) + 1;

			// Mesh subtype (see OvMesh SUBTYPE enum):
			unsigned char subtype;
			memcpy(&subtype, data + position, sizeof(unsigned char));
			char subtypeName[FILENAME_MAX];


			switch ((OvMesh::Subtype) subtype){
			case OvMesh::Subtype::DEFAULT: strcpy(subtypeName, "standard"); break;
			case OvMesh::Subtype::NORMALMAPPED: strcpy(subtypeName, "normal-mapped"); break;
			case OvMesh::Subtype::TESSELLATED: strcpy(subtypeName, "tessellated"); break;
			default: strcpy(subtypeName, "UNDEFINED");
			}
			position += sizeof(unsigned char);

			// Nr. of vertices:
			unsigned int vertices, faces;
			memcpy(&vertices, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// ...and faces:
			memcpy(&faces, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// Material name, or [none] if not used:
			char materialName[FILENAME_MAX];
			strcpy(materialName, data + position);

			position += (unsigned int)strlen(materialName) + 1;

			// Mesh bounding sphere radius:
			float radius;
			memcpy(&radius, data + position, sizeof(float));
			position += sizeof(float);

			// Mesh bounding box minimum corner:
			glm::vec3 bBoxMin;
			memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
			position += sizeof(glm::vec3);

			// Mesh bounding box maximum corner:
			glm::vec3 bBoxMax;
			memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
			position += sizeof(glm::vec3);

			// Optional physics properties:
			unsigned char hasPhysics;
			memcpy(&hasPhysics, data + position, sizeof(unsigned char));
			position += sizeof(unsigned char);
			if (hasPhysics){
				/**
				 * Mesh physics properties.
				 */
				struct PhysProps{
					// Pay attention to 16 byte alignement (use padding):
					unsigned char type;
					unsigned char contCollisionDetection;
					unsigned char collideWithRBodies;
					unsigned char hullType;

					// Vector data:
					glm::vec3 massCenter;

					// Mesh properties:
					float mass;
					float staticFriction;
					float dynamicFriction;
					float bounciness;
					float linearDamping;
					float angularDamping;
					void *physObj;
				};

				PhysProps mp;
				memcpy(&mp, data + position, sizeof(PhysProps));
				position += sizeof(PhysProps);

			}
			vector<Vertex> vecs;
			// Interleaved and compressed vertex/normal/UV/tangent data:
			for (unsigned int c = 0; c < vertices; c++){
				Vertex vert;

				// Vertex coords:
				glm::vec3 vertex;
				memcpy(&vertex, data + position, sizeof(glm::vec3));
				if (verbose) {
					vert.setPosition(vertex);
				}

				position += sizeof(glm::vec3);

				// Vertex normal:
				unsigned int normalData;
				memcpy(&normalData, data + position, sizeof(unsigned int));
				if (verbose){
					glm::vec4 normal = glm::unpackSnorm3x10_1x2(normalData);
					vert.setNormal(normal);
				}
				position += sizeof(unsigned int);

				// Texture coordinates:
				unsigned short textureData[2];
				memcpy(textureData, data + position, sizeof(unsigned short) * 2);
				if (verbose){
					glm::vec2 uv;
					uv.x = glm::unpackHalf1x16(textureData[0]);
					uv.y = glm::unpackHalf1x16(textureData[1]);
				}
				position += sizeof(unsigned short) * 2;

				// Tangent vector:
				unsigned int tangentData;
				memcpy(&tangentData, data + position, sizeof(unsigned int));
				if (verbose){
					glm::vec4 tangent = glm::unpackSnorm3x10_1x2(tangentData);
				}
				position += sizeof(unsigned int);


				glm::vec3 normal = glm::unpackSnorm3x10_1x2(normalData);
				glm::vec2 texture;
				texture.x = glm::unpackHalf1x16(textureData[0]);
				texture.y = glm::unpackHalf1x16(textureData[1]);
				vecs.emplace_back(Vertex(vertex.x, vertex.y, vertex.z, normal.x, normal.y, normal.z, texture.x, texture.y));
				//mesh->addVertex(vert);
			}

			// Faces:
			for (unsigned int c = 0; c < faces; c++){
				// Face indexes:
				unsigned int face[3];
				memcpy(face, data + position, sizeof(unsigned int) * 3);
				for(auto i : face) mesh->addVertex(vecs[i]);
				position += sizeof(unsigned int) * 3;
			}

			// Extra information for skinned meshes:
			if (isSkinned){
				// Initial mesh pose matrix:
				glm::mat4 poseMatrix;
				memcpy(&poseMatrix, data + position, sizeof(glm::mat4));
				//if (verbose)
				//	MAT2STR(poseMatrix);
				position += sizeof(glm::vec4);

				// Bone list:
				unsigned int nrOfBones;
				memcpy(&nrOfBones, data + position, sizeof(unsigned int));
				position += sizeof(unsigned int);

				for (unsigned int c = 0; c < nrOfBones; c++){
					// Bone name:
					char boneName[FILENAME_MAX];
					strcpy(boneName, data + position);
					position += (unsigned int)strlen(boneName) + 1;

					// Initial bone pose matrix (already inverted):
					glm::mat4 boneMatrix;
					memcpy(&boneMatrix, data + position, sizeof(glm::mat4));
					//if (verbose)
					//	MAT2STR(boneMatrix);
					position += sizeof(glm::mat4);
				}

				// Per vertex bone weights and indexes:
				for (unsigned int c = 0; c < vertices; c++){


					// Bone indexes:
					unsigned int boneIndex[4];
					memcpy(boneIndex, data + position, sizeof(unsigned int) * 4);
					position += sizeof(unsigned int) * 4;

					// Bone weights:
					unsigned short boneWeightData[4];
					memcpy(boneWeightData, data + position, sizeof(unsigned short) * 4);
					if (verbose){
						glm::vec4 boneWeight;
						boneWeight.x = glm::unpackHalf1x16(boneWeightData[0]);
						boneWeight.y = glm::unpackHalf1x16(boneWeightData[1]);
						boneWeight.z = glm::unpackHalf1x16(boneWeightData[2]);
						boneWeight.w = glm::unpackHalf1x16(boneWeightData[3]);
					}
					position += sizeof(unsigned short) * 4;
				}
			}

			//Insert the proper information about the mesh
			mesh->setName(meshName);
			mesh->setMatrix(matrix);
			mesh->setMaterial(materials.at(materialName));
			//Insert the mesh with is children in the vector
			obj.push_back(new Element{ mesh,children });
		}
		break;


		//////////////////////////////
		case OvObject::Type::LIGHT: {
			Light* light = new Light();
			// Light name:
			char lightName[FILENAME_MAX];
			strcpy(lightName, data + position);
			light->setName(lightName);
			position += (unsigned int)strlen(lightName) + 1;
			// Light matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			//if (verbose)
			//	MAT2STR(matrix);
			light->setMatrix(matrix);
			position += sizeof(glm::mat4);

			// Nr. of children nodes:
			memcpy(&children, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// Optional target node name, or [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy(targetName, data + position);
			position += (unsigned int)strlen(targetName) + 1;

			// Light subtype (see OvLight SUBTYPE enum):
			unsigned char subtype;
			memcpy(&subtype, data + position, sizeof(unsigned char));
			char subtypeName[FILENAME_MAX];
			switch ((OvLight::Subtype) subtype){
			case OvLight::Subtype::DIRECTIONAL: strcpy(subtypeName, "directional"); break;
			case OvLight::Subtype::OMNI: strcpy(subtypeName, "omni"); break;
			case OvLight::Subtype::SPOT: strcpy(subtypeName, "spot"); break;
			default: strcpy(subtypeName, "UNDEFINED");
			}
			position += sizeof(unsigned char);

			// Light color:
			glm::vec3 color;
			memcpy(&color, data + position, sizeof(glm::vec3));
			glm::vec4 colorVector(color.r, color.g,color.b, 1);

			//Convert the color for all our model of lights:
			light->setAmbient(colorVector);
			light->setDiffuse(colorVector);
			light->setShininess(128);
			light->setSpecular(colorVector);
			position += sizeof(glm::vec3);

			// Influence radius:
			float radius;
			memcpy(&radius, data + position, sizeof(float));
			position += sizeof(float);

			// Direction:
			glm::vec3 direction;
			memcpy(&direction, data + position, sizeof(glm::vec3));
			glm::vec4 dir(direction.r, direction.g, direction.b, 1);
			position += sizeof(glm::vec3);
            light->setDirection(dir);

			// Cutoff:
			float cutoff;
			memcpy(&cutoff, data + position, sizeof(float));
			position += sizeof(float);
			light->setCutoff(cutoff);

			// Exponent:
			float spotExponent;
			memcpy(&spotExponent, data + position, sizeof(float));
			position += sizeof(float);

			// Cast shadow flag:
			unsigned char castShadows;
			memcpy(&castShadows, data + position, sizeof(unsigned char));
			position += sizeof(unsigned char);

			// Volumetric lighting flag:
			unsigned char isVolumetric;
			memcpy(&isVolumetric, data + position, sizeof(unsigned char));
			position += sizeof(unsigned char);
			light->setType("light");
			obj.push_back(new Element{ light,children });
		}
		break;


		/////////////////////////////
		case OvObject::Type::BONE: {

			// Bone name:
			char boneName[FILENAME_MAX];
			strcpy(boneName, data + position);
			position += (unsigned int)strlen(boneName) + 1;

			// Bone matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			//if (verbose)
			//	MAT2STR(matrix);
			position += sizeof(glm::mat4);

			// Nr. of children nodes:
			memcpy(&children, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// Optional target node, or [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy(targetName, data + position);
			position += (unsigned int)strlen(targetName) + 1;

			// Mesh bounding box minimum corner:
			glm::vec3 bBoxMin;
			memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
			position += sizeof(glm::vec3);

			// Mesh bounding box maximum corner:
			glm::vec3 bBoxMax;
			memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
			position += sizeof(glm::vec3);
		}
		break;


		///////////
		default: //
			std::cout << "ERROR: corrupted or bad data in file " << filePath << endl;
			fclose(dat);
			delete[] data;
			return NULL;
		}

		// Release chunk memory:
		delete[] data;
	}

	// Done:
	fclose(dat);

	// Create the Tree with all the nodes:
	tree(obj);

	// Print the Tree with relationship
	//printTree(obj);

	return obj.at(0)->node;
}

