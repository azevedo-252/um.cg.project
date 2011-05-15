/**
 * Classe de gestao da camara
 */

#ifndef _camera_h
#define _camera_h

#include "Vertex.h"

class Camera {

public:
	static float persp_ratio;
	static int persp_ang;
	static int persp_z_near;
	static int persp_z_far;
        static Vertex *look_eye;
        static Vertex *look_center;
        static Vertex *look_up;
	
	Camera();

	void placeCamera();
};

#endif
