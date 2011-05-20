/**
 * Classe de gestao da camara
 */

#ifndef _camera_h
#define _camera_h

#include "Vertex.h"

class Camera {
public:
    
    bool set;
    static float persp_ratio;
    static int persp_ang;
    static int persp_z_near;
    static int persp_z_far;
    Vertex *camDir;
    Vertex *camPos;
    Vertex *camUp;

    Camera();

    void placeCamera();
};

#endif
