#include <GL/glut.h>

#include "Player.h"

extern Player* g_player;

#include "Camera.h"
#include "InputManager.h"
#include "Map.h"

#include "externs.h"
#include <math.h>

float Camera::persp_ratio;
int Camera::persp_ang;
int Camera::persp_z_near;
int Camera::persp_z_far;

Camera::Camera() {
	Camera::persp_ratio = 1;
	Camera::persp_ang = conf.rint("camera:persp_ang");
	Camera::persp_z_near = conf.rint("camera:persp_z_near");
	Camera::persp_z_far = conf.rint("camera:persp_z_far");
	this->camPos = new Vertex();
	this->camDir = new Vertex();
	this->camUp = new Vertex(0, 1, 0);
	
	terrain_offset = conf.rfloat("camera:terrain_offset");

	set = false;
}

void Camera::placeCamera() {
	Vertex* pos = g_player->coords;
	Vertex* dir = g_player->direction;

	glLoadIdentity();

	int cam_mode = InputManager::getOpState(CAMERA_MODE);

	if (cam_mode == KEY_OFF) {
		int tps_off = conf.rint("camera:tps_off");
		int tps_y_off = conf.rint("camera:tps_y_off");
		int tps_dir_y_off = conf.rint("camera:tps_dir_y_off");

		camPos->x = pos->x - tps_off * dir->x;
		camPos->z = pos->z - tps_off * dir->z;
		camPos->y = max(pos->y - tps_off * dir->y + tps_y_off, g_map->triangulateHeight(camPos->x, camPos->z) + terrain_offset);

		camDir->x = pos->x;
		camDir->y = pos->y + tps_dir_y_off;
		camDir->z = pos->z;
	} else {
		int fps_off = conf.rint("camera:fps_off");
		int fps_y_off = conf.rint("camera:fps_y_off");
		int fps_dir_y_off = conf.rint("camera:fps_dir_y_off");

		camPos->x = pos->x + fps_off * dir->x;
		camPos->z = pos->z + fps_off * dir->x;
		camPos->y = max(pos->y + fps_y_off, g_map->triangulateHeight(camPos->x, camPos->z));

		camDir->x = pos->x + (fps_off + 1) * dir->x;
		camDir->y = pos->y + dir->y + fps_dir_y_off;
		camDir->z = pos->z + (fps_off + 1) * dir->z;
	}


	gluLookAt(camPos->x, camPos->y, camPos->z,
		camDir->x, camDir->y, camDir->z,
		0, 1, 0);
}
