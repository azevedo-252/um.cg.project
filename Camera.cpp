#include <GL/glut.h>

#include "Player.h"

extern Player* g_player;

#include "Camera.h"
#include "InputManager.h"

#include <math.h>

float Camera::persp_ratio;
int Camera::persp_ang;
int Camera::persp_z_near;
int Camera::persp_z_far;
Vertex *Camera::look_eye;
Vertex *Camera::look_center;
Vertex *Camera::look_up;

Camera::Camera() {
    Camera::persp_ratio = 1;
    Camera::persp_ang = conf.rint("camera:persp_ang");
    Camera::persp_z_near = conf.rint("camera:persp_z_near");
    Camera::persp_z_far = conf.rint("camera:persp_z_far");
    Camera::look_eye = new Vertex();
    Camera::look_center = new Vertex();
    Camera::look_up = new Vertex(0, 1, 0);
    
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

        gluLookAt(pos->x - tps_off * dir->x,
                pos->y - tps_off * dir->y + tps_y_off,
                pos->z - tps_off * dir->z,

                pos->x,
                pos->y + tps_dir_y_off,
                pos->z,

                0, 1, 0);
        Camera::look_eye->x = pos->x - tps_off * dir->x;
        Camera::look_eye->y = pos->y - tps_off * dir->y + tps_y_off;
        Camera::look_eye->z = pos->z - tps_off * dir->z;
        Camera::look_center->x = pos->x;
        Camera::look_center->y = pos->y + tps_dir_y_off;
        Camera::look_center->z = pos->z;
        

    } else {
        int fps_off = conf.rint("camera:fps_off");
        int fps_y_off = conf.rint("camera:fps_y_off");
        int fps_dir_y_off = conf.rint("camera:fps_dir_y_off");

        gluLookAt(pos->x + fps_off * dir->x,
                pos->y + fps_y_off,
                pos->z + fps_off * dir->z,

                pos->x + (fps_off + 1) * dir->x,
                pos->y + dir->y + fps_dir_y_off,
                pos->z + (fps_off + 1) * dir->z,

                0, 1, 0);
        Camera::look_eye->x = pos->x + fps_off * dir->x;
        Camera::look_eye->y = pos->y + fps_y_off;
        Camera::look_eye->z = pos->z + fps_off * dir->z;
        Camera::look_center->x = pos->x + (fps_off + 1) * dir->x;
        Camera::look_center->y = pos->y + dir->y + fps_dir_y_off;
        Camera::look_center->z = pos->z + (fps_off + 1) * dir->z;
    }
}
