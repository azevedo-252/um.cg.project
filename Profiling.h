/* 
 * File:   Profiling.h
 * Author: gabriel
 *
 * Created on 29 de Abril de 2011, 10:39
 */

#ifndef PROFILING_H
#define	PROFILING_H

#include "Vertex.h"


class Profiling {
public:
    Profiling();
    void render();
private:
    float timebase, time;
    int fps, frame;
    Vertex *screen_coords;
    void setOrthographicProjection();
    void resetPerspectiveProjection();
    void update();
};

#endif	/* PROFILING_H */

