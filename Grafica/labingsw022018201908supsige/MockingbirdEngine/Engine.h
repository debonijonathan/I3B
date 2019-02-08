#pragma once
// Generic info:
#define LIB_NAME      "Graphic Engine"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)

#include "LibApi.h"

#include "Vertex.h"
#include "Object.h"
#include "Node.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Light.h"
#include "List.h"
#include "OvoReader.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#define ARROW_UP 101
#define ARROW_DOWN 103
#define ARROW_RIGHT 102
#define ARROW_LEFT 100
#define F1 1
#define F2 2
#define F3 3
#define F4 4
#define F5 5
#define F6 6
#define F7 7
#define F8 8
#define F9 9
#define F9 9
#define F10 10
#define MOUSE_LEFT_BUTTON 0
#define CLICK_DOWN 0

using namespace std;
class LIB_API Engine{
    public:
        static Engine& getEngine();
        ~Engine();
        static void init(int argc, char **argv, const char *title);
        static void option();
        void loadGeometryFile(const char* filePath);
        void loop();
        void changeWireframe();
		void changeFpsToggle();
		void changeCamera();
        void forwardCamera(glm::vec4 out_of_bounds, bool flag);
        void backwardCamera(glm::vec4 out_of_bounds, bool flag);
        void toLeftCamera(glm::vec4 out_of_bounds, bool flag);
        void toRightCamera(glm::vec4 out_of_bounds, bool flag);
		static void setTrasformation(Node* node, glm::mat4 transformation);
        void setKeyboardCallback(void (* keyboardCallback) (unsigned char, int, int));
        void setSpecialCallback(void (* specialCallback) (int, int, int));
        void setMouseCallback(void (* mouseCallback) (int, int, int, int));
        void setMotionCallback(void (* motionCallback) (int, int));
		bool getWireframe();
		bool getFpsToggle();
        Node* getNodeByName(string name);
		static void setMirror(bool flag);
        static Camera camera;
		static Camera camera2;
		static List* getList();
private:
        Engine();
        void loadAllElements(Node* node);
        Node* root;
        static void displayCallback();
        static void reshapeCallback(int width, int height);
        static void (* keyboardCallback) (unsigned char, int, int);
        static void (* specialCallback) (int, int, int);
		static void (* mouseCallback)(int, int, int, int);
		static void (* motionCallback)(int, int);
		static void timerCallback(int value);
        static int windowId;
        static bool wireframe;
		static bool fpsToggle;
        static bool left_mouse_down;
		static bool originalCamera;
        static int oldx;
        static int oldy;
		static List *listm;
		static Engine instance;
};

