/* 
 * File:   Frustum.h
 * Author: gabriel
 *
 * Created on May 15, 2011, 4:32 PM
 */

#ifndef FRUSTUM_H
#define	FRUSTUM_H

#include "Vertex.h"
#include "Plane.h"

class Frustum {
    
private:

    enum {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEARP,
        FARP
    };


public:

    enum {
        OUTSIDE, INTERSECT, INSIDE
    };

    Plane pl[6];


    Vertex ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
    float nearD, farD, ratio, angle, tang;
    float nw, nh, fw, fh;

    Frustum();
    ~Frustum();

    void setCamInternals(float angle, float ratio, float nearD, float farD);
    void setCamDef(Vertex *p, Vertex *l, Vertex *u);
    int pointInFrustum(Vertex *p);
    int sphereInFrustum(Vertex *p, float raio);
    //int boxInFrustum(AABox &b);

    void drawPoints();
    void drawLines();
    void drawPlanes();
    void drawNormals();
    
};

#endif	/* FRUSTUM_H */

