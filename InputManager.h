/**
 * Gestor do input do teclado/rato
 */

#ifndef _inputmanager_h
#define _inputmanager_h

#include <GL/glut.h>

#define KEY_OFF 0
#define KEY_ON  1
#define KEY_UNDEF -1

#define KEY_ASCII_ESC	27
#define KEY_ASCII_SPACE	32

typedef enum e_key_code {
	KEY_A,
	KEY_W,
	KEY_S,
	KEY_D,
	KEY_SPACE,

	MOUSE_X,
	MOUSE_Y,

	MOUSE_OFF_X,
	MOUSE_OFF_Y,

	KEY_COUNT,
	KEY_VOID,
} KEY_CODE;

typedef enum e_op_code {
	CAMERA_MODE,

	OP_COUNT,
	OP_VOID,
} OP_CODE;

class InputManager {
private:
	static int keys[KEY_COUNT];
	static int ops[OP_COUNT];
	static int mouse_x, mouse_y;

public:
	static void init();

	/** funcao para gerir o input ASCII do teclado */
	static void keyboardFunc(unsigned char key, int mouse_x, int mouse_y);

	/** funcao para gerir as teclas largadas */
	static void keyboardUpFunc(unsigned char key, int mouse_x, int mouse_y);

	/** funcao para gerir o input nao ASCII do teclado */
	static void keyboardSpecialFunc(int key, int mouse_x, int mouse_y);

	static void mouseButtons(int button, int state, int x, int y);

	static void mouseMotion(int xx, int yy);

	static int getKeyState(KEY_CODE code);

	static int getOpState(OP_CODE code);

	static void resetMouseMove();

private:
	/** define um estado para uma tecla */
	static void setKeyState(unsigned char key, int state);
	static void setOpState(int key);
	static void setSpecialKeyState(int key, int state);

};
#endif
