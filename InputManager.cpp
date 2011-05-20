#include <stdio.h>

#include "InputManager.h"
#include "GLManager.h"
#include <GL/glut.h>

#include "externs.h"

int InputManager::keys[KEY_COUNT];
int InputManager::ops[OP_COUNT];
int InputManager::mouse_x, InputManager::mouse_y;

void InputManager::init() {
	for(int i = 0; i < KEY_COUNT; i++) {
		keys[i] = KEY_OFF;
	}
	mouse_x = KEY_UNDEF;
	mouse_y = KEY_UNDEF;

	for(int i = 0; i < OP_COUNT; i++) {
		ops[i] = KEY_OFF;
	}
}

void InputManager::keyboardFunc(unsigned char key, int mouse_x, int mouse_y) {
	InputManager::setKeyState(key, KEY_ON);
	InputManager::setOpState((int) key);
}

void InputManager::keyboardUpFunc(unsigned char key, int mouse_x, int mouse_y) {
	InputManager::setKeyState(key, KEY_OFF);
}

void InputManager::keyboardSpecialFunc(int key, int mouse_x, int mouse_y) {
	switch(key) {
		case GLUT_KEY_F1:
			glPolygonMode(GL_FRONT, GL_LINE);
			break;
		case GLUT_KEY_F2:
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
	}

}

void InputManager::mouseButtons(int button, int state, int xx, int yy) {
	/**if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
	else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {			
			r -= yy - startY;
			if (r < 3)
			r = 3.0;
		}
		tracking = 0;
	}*/
}

void InputManager::mouseMotion(int xx, int yy) {
	static bool done = false;

	if (!done) {

		keys[MOUSE_OFF_X] += xx - g_win_half_w;
		keys[MOUSE_OFF_Y] += yy - g_win_half_h;
		keys[MOUSE_X] = xx;
		keys[MOUSE_Y] = yy;

		glutWarpPointer(g_win_half_w, g_win_half_h);
	}

	done = !done;
}

int InputManager::getKeyState(KEY_CODE code) {
	return keys[code];
}

int InputManager::getOpState(OP_CODE code) {
	return ops[code];
}

void InputManager::resetMouseMove() {
	keys[MOUSE_OFF_X] = 0;
	keys[MOUSE_OFF_Y] = 0;
}

void InputManager::setOpState(int key) {
	OP_CODE op_code = OP_VOID;

	switch(key) {
		case 'c':
		case 'C':
			op_code = CAMERA_MODE;
	}

	if (op_code != -1) {
		ops[op_code] = 1 - ops[op_code];
	}
}

void InputManager::setKeyState(unsigned char key, int state) {

	KEY_CODE key_code = KEY_VOID;

	switch(key) {
		case 'a':
		case 'A':
			key_code = KEY_A;
			break;

		case 'd':
		case 'D':
			key_code = KEY_D;
			break;

		case 'w':
		case 'W':
			key_code = KEY_W;
			break;

		case 's':
		case 'S':
			key_code = KEY_S;
			break;
			
		case 'm':
		case 'M':
			if (state == KEY_ON)
				Sound::toogleMusic();
			break;
			
		case KEY_ASCII_SPACE:
			key_code = KEY_SPACE;
			break;

		case KEY_ASCII_ESC:
			exit(0);
			break;
	}

	if (key_code != KEY_VOID)
		keys[key_code] = state;
}

void InputManager::setSpecialKeyState(int key, int state) {

	switch(key) {
	}
}
