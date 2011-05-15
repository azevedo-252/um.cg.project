/* 
 * File:   Plane.h
 * Author: gabriel
 *
 * Created on May 15, 2011, 6:27 PM
 */

#ifndef PLANE_H
#define	PLANE_H

#include "Vertex.h"

class Plane {
public:
    Plane(Vertex *v1,  Vertex *v2,  Vertex *v3);
    void set3Points(Vertex *v1, Vertex *v2, Vertex *v3);
    void setNormalAndPoint(Vertex *normal, Vertex *point);
    void setCoefficients(float a, float b, float c, float d);
    float distance(Vertex *p);
private:
    Vertex *normal, *point;
    float d;
};

#endif	/* PLANE_H */

