#include "Engine.h"
#include <glm/glm.hpp>
#include<iostream>
#include <string>

#define MAX_FINGER_ITERATION 30
#define MIN_FINGER_ITERATION -1
#define MAX_THUMB_ITERATION 10

Engine ge = Engine::getEngine();
float angle = 1.0f;
int constraint[] = { 0,0,0,0,0 };

// The rotation of the fingers :
glm::mat4 fingerBaseRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0,0,1));
glm::mat4 fingerMiddleRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle*2), glm::vec3(0,0,1));
glm::mat4 fingerTipRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle*3), glm::vec3(0,0,1));

glm::mat4 fingerBaseRotationMatrixXAxis = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1,0,0));
glm::mat4 fingerMiddleRotationMatrixXAxis = glm::rotate(glm::mat4(1.0f), glm::radians(angle*2), glm::vec3(1,0,0));
glm::mat4 fingerTipRotationMatrixXAxis = glm::rotate(glm::mat4(1.0f), glm::radians(angle*3), glm::vec3(1,0,0));


// The name of the lights used :
std::string omniLight = "OmniLight";
std::string spotLight = "Spotlight";
bool left_mouse_down = false;
int oldx = 0;
int oldy = 0;

//////////////////////
// keyboardCallback //
//////////////////////

/**
 * this method allows us to specify what to do with the various keys
 * @param the key pressed and the coordinates of the mouse
 * @return void
 */
void keyboardCallback(unsigned char key, int mouseX, int mouseY){
	const float speed = 1.0f;
	const char esc = (char)27;
	glm::vec4 out_of_bounds(68.5f, 68.5f, 68.5f, 0.1f);
	switch (key)
	{
		case ' ':
			ge.setTrasformation(ge.getNodeByName("Wrist"), glm::rotate(glm::mat4(1.0f), glm::radians(angle*2), glm::vec3(0, 1, 0)));
			break;
		case 'l':
		case 'L':
			ge.changeWireframe();
			break;
		case 'f':
		case 'F':
			ge.changeFpsToggle();
			break;
		case 'w':
		case 'W':
			ge.forwardCamera(out_of_bounds, true);
			break;
		case 's':
		case 'S':
			ge.backwardCamera(out_of_bounds,true);
			break;
		case 'a':
		case 'A':
			ge.toLeftCamera(out_of_bounds, true);
			break;
        case 'd':
        case 'D':
            ge.toRightCamera(out_of_bounds, true);
            break;
		case 'm':
		case 'M':
			ge.setTrasformation(ge.getNodeByName(omniLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, speed, 0)));
			break;
		case 'n':
		case 'N':
			ge.setTrasformation(ge.getNodeByName(omniLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, -speed, 0)));
			break;
		case 'u':
		case 'U':
			ge.setTrasformation(ge.getNodeByName(omniLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -speed)));
			break;
		case 'j':
		case 'J':
			ge.setTrasformation(ge.getNodeByName(omniLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, speed)));
			break;
		case 'h':
		case 'H':
			ge.setTrasformation(ge.getNodeByName(omniLight), glm::translate(glm::mat4(1.0f), glm::vec3(-speed, 0, 0)));
			break;
		case 'k':
		case 'K':
			ge.setTrasformation(ge.getNodeByName(omniLight), glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0, 0)));
			break;
		case '5':
			ge.setTrasformation(ge.getNodeByName(spotLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, speed, 0)));
			break;
		case '1':
			ge.setTrasformation(ge.getNodeByName(spotLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, -speed, 0)));
			break;
		case '8':
			ge.setTrasformation(ge.getNodeByName(spotLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -speed)));
			break;
		case '2':
			ge.setTrasformation(ge.getNodeByName(spotLight), glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, speed)));
			break;
		case '4':
			ge.setTrasformation(ge.getNodeByName(spotLight), glm::translate(glm::mat4(1.0f), glm::vec3(-speed, 0, 0)));
			break;
		case '6':
			ge.setTrasformation(ge.getNodeByName(spotLight), glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0, 0)));
			break;
		case 'c':
		case 'C':
			ge.changeCamera();
			break;
	}
}

/////////////////////
// specialCallback //
/////////////////////

/**
 * this method allows us to specify what to do with the various special keys
 * @param the special key pressed and the coordinates of the mouse
 * @return void
 */
void specialCallback(int key, int mouseX, int mouseY){
    switch (key)
    {
        case ARROW_DOWN:
			if (constraint[0] < MAX_THUMB_ITERATION) {
				constraint[0]++;
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), glm::inverse(fingerTipRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), glm::inverse(fingerBaseRotationMatrixXAxis));
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), glm::inverse(fingerTipRotationMatrixXAxis));
			}

			if (constraint[1] < MAX_FINGER_ITERATION) {
				constraint[1]++;
				ge.setTrasformation(ge.getNodeByName("Index_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Index_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Index_tip"), glm::inverse(fingerTipRotationMatrix));
			}
			
			if (constraint[2] < MAX_FINGER_ITERATION) {
				constraint[2]++;
				ge.setTrasformation(ge.getNodeByName("Middle_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Middle_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Middle_tip"), glm::inverse(fingerTipRotationMatrix));
			}
			
			if (constraint[3] < MAX_FINGER_ITERATION) {
				constraint[3]++;
				ge.setTrasformation(ge.getNodeByName("Ring_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Ring_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Ring_tip"), glm::inverse(fingerTipRotationMatrix));
			}

			if (constraint[4] < MAX_FINGER_ITERATION) {
				constraint[4]++;
				ge.setTrasformation(ge.getNodeByName("Pinky_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Pinky_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Pinky_tip"), glm::inverse(fingerTipRotationMatrix));
			}
		break;

		case ARROW_UP:
			if (constraint[0] > MIN_FINGER_ITERATION) {
				constraint[0]--;
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), fingerTipRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), fingerBaseRotationMatrixXAxis);
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), fingerTipRotationMatrixXAxis);
			}
			
			if (constraint[1] > MIN_FINGER_ITERATION) {
				constraint[1]--;
				ge.setTrasformation(ge.getNodeByName("Index_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Index_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Index_tip"), fingerTipRotationMatrix);
			}

			if (constraint[2] > MIN_FINGER_ITERATION) {
				constraint[2]--;
				ge.setTrasformation(ge.getNodeByName("Middle_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Middle_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Middle_tip"), fingerTipRotationMatrix);
			}

			if (constraint[3] > MIN_FINGER_ITERATION) {
				constraint[3]--;
				ge.setTrasformation(ge.getNodeByName("Ring_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Ring_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Ring_tip"), fingerTipRotationMatrix);
			}

			if (constraint[4] > MIN_FINGER_ITERATION) {
				constraint[4]--;
				ge.setTrasformation(ge.getNodeByName("Pinky_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Pinky_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Pinky_tip"), fingerTipRotationMatrix);
			}
		break;

		case F1:
			if (constraint[0] < MAX_THUMB_ITERATION) {
				constraint[0]++;
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), glm::inverse(fingerTipRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), glm::inverse(fingerBaseRotationMatrixXAxis));
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), glm::inverse(fingerTipRotationMatrixXAxis));
			}
			break;

		case F2:
			if (constraint[1] < MAX_FINGER_ITERATION) {
				constraint[1]++;
				ge.setTrasformation(ge.getNodeByName("Index_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Index_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Index_tip"), glm::inverse(fingerTipRotationMatrix));
			}
			break;

		case F3:
			if (constraint[2] < MAX_FINGER_ITERATION) {
				constraint[2]++;
				ge.setTrasformation(ge.getNodeByName("Middle_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Middle_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Middle_tip"), glm::inverse(fingerTipRotationMatrix));
			}
			break;

		case F4:
			if (constraint[3] < MAX_FINGER_ITERATION) {
				constraint[3]++;
				ge.setTrasformation(ge.getNodeByName("Ring_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Ring_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Ring_tip"), glm::inverse(fingerTipRotationMatrix));
			}
			break;

		case F5:
			if (constraint[4] < MAX_FINGER_ITERATION) {
				constraint[4]++;
				ge.setTrasformation(ge.getNodeByName("Pinky_base"), glm::inverse(fingerBaseRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Pinky_middle"), glm::inverse(fingerMiddleRotationMatrix));
				ge.setTrasformation(ge.getNodeByName("Pinky_tip"), glm::inverse(fingerTipRotationMatrix));
			}
			break;

		case F6:
			if (constraint[0] > MIN_FINGER_ITERATION) {
				constraint[0]--;
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), fingerTipRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Thumb_base"), fingerBaseRotationMatrixXAxis);
				ge.setTrasformation(ge.getNodeByName("Thumb_tip"), fingerTipRotationMatrixXAxis);
			}
			break;

		case F7:
			if (constraint[1] > MIN_FINGER_ITERATION) {
				constraint[1]--;
				ge.setTrasformation(ge.getNodeByName("Index_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Index_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Index_tip"), fingerTipRotationMatrix);
			}
			break;

		case F8:
			if (constraint[2] > MIN_FINGER_ITERATION) {
				constraint[2]--;
				ge.setTrasformation(ge.getNodeByName("Middle_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Middle_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Middle_tip"), fingerTipRotationMatrix);
			}
			break;

		case F9:
			if (constraint[3] > MIN_FINGER_ITERATION) {
				constraint[3]--;
				ge.setTrasformation(ge.getNodeByName("Ring_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Ring_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Ring_tip"), fingerTipRotationMatrix);
			}
			break;

		case F10:
			if (constraint[4] > MIN_FINGER_ITERATION) {
				constraint[4]--;
				ge.setTrasformation(ge.getNodeByName("Pinky_base"), fingerBaseRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Pinky_middle"), fingerMiddleRotationMatrix);
				ge.setTrasformation(ge.getNodeByName("Pinky_tip"), fingerTipRotationMatrix);
			}
			break;
    }
}


///////////////////
// mouseCallback //
///////////////////

/**
 * this method sets the mouse callback for the window.
 * @param the x and y callback parameters indicate the window relative coordinates when the mouse button state changed
 * @return void
 */
void mouseCallback(int button, int state, int x, int y){
    if (button == MOUSE_LEFT_BUTTON && state == CLICK_DOWN) {
        oldx = x;
        oldy = y;
        left_mouse_down = true;
    } else
        left_mouse_down = false;
}

///////////////////
// mouseCallback //
///////////////////

/**
 * The motion callback for a window is called when the mouse moves within the window while the mouse buttons are pressed
 * @param the x and y callback parameters indicate the mouse location in window relative coordinates.
 * @return void
 */
void motionCallback(int x, int y){
    if(left_mouse_down){
        glm::vec3 norm_dir = glm::normalize(ge.camera.getDirection());
        //In OpenGL xyz equals to yzx
        float dx = (x - oldx)*ge.camera.getMotionSpeed(), dy = (y - oldy)*ge.camera.getMotionSpeed();
        oldx = x;
        oldy = y;
        float pitch = asin(norm_dir.y);
        float yaw = atan2(norm_dir.z/cos(pitch), norm_dir.x/cos(pitch));

        yaw += glm::radians(dx);
        pitch -= glm::radians(dy);

        if (pitch > glm::radians(89.0f)) {
            pitch = glm::radians(89.0f);
        }
        if (pitch < glm::radians(-89.0f)) {
            pitch = glm::radians(-89.0f);
        }

        float new_x, new_y, new_z;
        new_x = cos(pitch) * cos(yaw);
        new_y = sin(pitch);
        new_z = sin(yaw) * cos(pitch);
        glm::vec3 new_dir(new_x,new_y,new_z);
        ge.camera.setDirection(new_dir);
    }
}

//////////
// main //
//////////

/**
 * Application entry point. Through this method we put the information from the window and what scene to represent
 * @param the arguments of the main
 * @return the status of the application
 */
int main(int argc, char **argv) {
	ge.setKeyboardCallback(keyboardCallback);
	ge.setSpecialCallback(specialCallback);
	ge.setMouseCallback(mouseCallback);
	ge.setMotionCallback(motionCallback);
	ge.loadGeometryFile("scene/finalTransparent.OVO");
	ge.setMirror(true);
	ge.changeFpsToggle();
	ge.init(argc, argv, "The Thanos glove");
	ge.loop();
	return 0;
}
