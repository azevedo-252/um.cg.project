/* 
 * File:   Frustum.cpp
 * Author: gabriel
 * 
 * Created on May 15, 2011, 4:32 PM
 */

#define ANG2RAD 3.14159265358979323846/180.0

#include "Frustum.h"
#include "externs.h"

Frustum::Frustum() {

}

void Frustum::setCamInternals(float angle, float ratio, float nearD, float farD) {

    this->ratio = ratio;
    this->angle = angle;
    this->nearD = nearD;
    this->farD = farD;

    tang = (float) tan(angle * ANG2RAD * 0.5);
    nh = nearD * tang;
    nw = nh * ratio;
    fh = farD * tang;
    fw = fh * ratio;


}

void Frustum::setCamDef(Vertex *p, Vertex *l, Vertex *u) {

    Vertex dir, nc, fc, X, Y, Z;
    
    Vertex aux1, aux2, aux3;

    Z = *p - *l;
    Z.normalize();

    X = *u * Z;
    X.normalize();

    Y = Z * X;

    //Z.mult(nearD);
    aux1 = Z * nearD;
    nc = *p - aux1;
    //Z.mult(farD);
    aux1 = Z * farD;
    fc = *p - aux1;
    
    aux1 = X * nw;
    aux2 = Y * nh;
    aux3 = aux2 - aux1;
    ntl = aux3 + nc;
    
    aux1 = X * nw;
    aux2 = Y * nh;
    aux3 = aux2 + aux1;
    ntr = aux3 + nc;    
    
    aux1 = X * nw;
    aux2 = Y * nh;
    aux3 = aux2 + aux1;
    nbl = nc - aux3;        
    
    aux1 = X * nw;
    aux2 = Y * nh;
    aux3 = aux1 - aux2;
    nbr = nc + aux3;            
    
    aux1 = X * fw;
    aux2 = Y * fh;
    aux3 = aux2 - aux1;
    ftl = aux3 + fc;
    
    aux1 = X * fw;
    aux2 = Y * fh;
    aux3 = aux2 + aux1;
    ftr = aux3 + fc;    
    
    aux1 = X * fw;
    aux2 = Y * fh;
    aux3 = aux2 + aux1;
    fbl = fc - aux3;        
    
    aux1 = X * fw;
    aux2 = Y * fh;
    aux3 = aux1 - aux2;
    fbr = fc + aux3;                

    /*
    ntl = nc + Y * nh - X * nw;
    ntr = nc + Y * nh + X * nw;
    nbl = nc - Y * nh - X * nw;
    nbr = nc - Y * nh + X * nw;

    ftl = fc + Y * fh - X * fw;
    ftr = fc + Y * fh + X * fw;
    fbl = fc - Y * fh - X * fw;
    fbr = fc - Y * fh + X * fw;
    */
    
    pl[TOP].set3Points(&ntr, &ntl, &ftl);
    pl[BOTTOM].set3Points(&nbl, &nbr, &fbr);
    pl[LEFT].set3Points(&ntl, &nbl, &fbl);
    pl[RIGHT].set3Points(&nbr, &ntr, &fbr);
    pl[NEARP].set3Points(&ntl, &ntr, &nbr);
    pl[FARP].set3Points(&ftr, &ftl, &fbl);
    
}

int Frustum::sphereInFrustum(Vertex *p, float raio) {

    int result = INSIDE;
    float distance;

    for (int i = 0; i < 6; i++) {
        distance = pl[i].distance(p);
        if (distance < -raio)
            return OUTSIDE;
        else if (distance < raio)
            result = INTERSECT;
    }
    return (result);

}

void Frustum::drawPoints() {


    glBegin(GL_POINTS);

    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(nbl.x, nbl.y, nbl.z);
    glVertex3f(nbr.x, nbr.y, nbr.z);

    glVertex3f(ftl.x, ftl.y, ftl.z);
    glVertex3f(ftr.x, ftr.y, ftr.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);

    glEnd();
}

void Frustum::drawLines() {

    glBegin(GL_LINE_LOOP);
    //near plane
    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(nbr.x, nbr.y, nbr.z);
    glVertex3f(nbl.x, nbl.y, nbl.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //far plane
    glVertex3f(ftr.x, ftr.y, ftr.z);
    glVertex3f(ftl.x, ftl.y, ftl.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //bottom plane
    glVertex3f(nbl.x, nbl.y, nbl.z);
    glVertex3f(nbr.x, nbr.y, nbr.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //top plane
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(ftl.x, ftl.y, ftl.z);
    glVertex3f(ftr.x, ftr.y, ftr.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //left plane
    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(nbl.x, nbl.y, nbl.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);
    glVertex3f(ftl.x, ftl.y, ftl.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // right plane
    glVertex3f(nbr.x, nbr.y, nbr.z);
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(ftr.x, ftr.y, ftr.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);

    glEnd();
}

void Frustum::drawPlanes() {

    glBegin(GL_QUADS);

    //near plane
    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(nbr.x, nbr.y, nbr.z);
    glVertex3f(nbl.x, nbl.y, nbl.z);

    //far plane
    glVertex3f(ftr.x, ftr.y, ftr.z);
    glVertex3f(ftl.x, ftl.y, ftl.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);

    //bottom plane
    glVertex3f(nbl.x, nbl.y, nbl.z);
    glVertex3f(nbr.x, nbr.y, nbr.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);

    //top plane
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(ftl.x, ftl.y, ftl.z);
    glVertex3f(ftr.x, ftr.y, ftr.z);

    //left plane

    glVertex3f(ntl.x, ntl.y, ntl.z);
    glVertex3f(nbl.x, nbl.y, nbl.z);
    glVertex3f(fbl.x, fbl.y, fbl.z);
    glVertex3f(ftl.x, ftl.y, ftl.z);

    // right plane
    glVertex3f(nbr.x, nbr.y, nbr.z);
    glVertex3f(ntr.x, ntr.y, ntr.z);
    glVertex3f(ftr.x, ftr.y, ftr.z);
    glVertex3f(fbr.x, fbr.y, fbr.z);

    glEnd();

}
/*
void Frustum::drawNormals() {

    Vertex a, b;

    glBegin(GL_LINES);

    // near
    a = (ntr + ntl + nbr + nbl) * 0.25;
    b = a + pl[NEARP].normal;
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);

    // far
    a = (ftr + ftl + fbr + fbl) * 0.25;
    b = a + pl[FARP].normal;
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);

    // left
    a = (ftl + fbl + nbl + ntl) * 0.25;
    b = a + pl[LEFT].normal;
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);

    // right
    a = (ftr + nbr + fbr + ntr) * 0.25;
    b = a + pl[RIGHT].normal;
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);

    // top
    a = (ftr + ftl + ntr + ntl) * 0.25;
    b = a + pl[TOP].normal;
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);

    // bottom
    a = (fbr + fbl + nbr + nbl) * 0.25;
    b = a + pl[BOTTOM].normal;
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);

    glEnd();


}*/