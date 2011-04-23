#include <GL/glut.h>

#include "Player.h"

extern Player* g_player;

#include "Camera.h"
#include "InputManager.h"

#include <math.h>

Camera::Camera() {

}

void Camera::placeCamera() {
	Vertex* pos = g_player->coords;
	Vertex* dir = g_player->direction;

	glLoadIdentity();

	int cam_mode = InputManager::getOpState(CAMERA_MODE);

	if (cam_mode == KEY_OFF) {
		int tps_off		= conf.rint("camera:tps_off");
		int tps_y_off	= conf.rint("camera:tps_y_off");
		int tps_dir_y_off = conf.rint("camera:tps_dir_y_off");

		gluLookAt(	pos->x - tps_off * dir->x,
					pos->y - tps_off * dir->y + tps_y_off,
					pos->z - tps_off * dir->z,

					pos->x,
					pos->y + tps_dir_y_off,
					pos->z,

					0, 1, 0);
	}
	else {
		int fps_off			= conf.rint("camera:fps_off");
		int fps_y_off		= conf.rint("camera:fps_y_off");
		int fps_dir_y_off	= conf.rint("camera:fps_dir_y_off");

		gluLookAt(	pos->x + fps_off * dir->x,
					pos->y + fps_y_off,
					pos->z + fps_off * dir->z,

					pos->x + (fps_off + 1) * dir->x,
					pos->y + dir->y + fps_dir_y_off,
					pos->z + (fps_off + 1) * dir->z,

					0, 1, 0);
	}
}
