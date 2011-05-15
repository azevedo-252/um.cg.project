/* 
 * File:   Frustum.h
 * Author: gabriel
 *
 * Created on May 15, 2011, 4:32 PM
 */

#ifndef FRUSTUM_H
#define	FRUSTUM_H

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

    static enum {
        OUTSIDE, INTERSECT, INSIDE
    };

    Plane pl[6];


    Vertex ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
    float nearD, farD, ratio, angle, tang;
    float nw, nh, fw, fh;

    Frustum::Frustum();
    Frustum::~Frustum();

    void Frustum::setCamInternals(float angle, float ratio, float nearD, float farD);
    void Frustum::setCamDef(Vertex &p, Vertex &l, Vertex &u);
    int Frustum::pointInFrustum(Vertex &p);
    int Frustum::sphereInFrustum(Vertex &p, float raio);
    //int Frustum::boxInFrustum(AABox &b);

    void Frustum::drawPoints();
    void Frustum::drawLines();
    void Frustum::drawPlanes();
    void Frustum::drawNormals();
    
};

#endif	/* FRUSTUM_H */

