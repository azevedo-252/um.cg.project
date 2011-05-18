/* 
 * File:   Profiling.cpp
 * Author: gabriel
 * 
 * Created on May 18, 2011, 1:01 AM
 */

#include "externs.h"
#include "Profiling.h"

Profiling::Profiling() {
    old_count = new_count = glutGet(GLUT_ELAPSED_TIME);
    frames = fps = 0;
}

void Profiling::update() {
    new_count = glutGet(GLUT_ELAPSED_TIME);
    frames++;
    if (new_count - old_count > 1000) {
        fps = frames * 1000 / (new_count - old_count);
        frames = 0;
        old_count = new_count;
    }
}

void Profiling::setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);
    glScalef(1, -1, 1);
    glTranslatef(100, -200, 0);
    glMatrixMode(GL_MODELVIEW);
}

void Profiling::resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Profiling::render() {
    glPushMatrix();
    glLoadIdentity();
    setOrthographicProjection();
    glRasterPos2i(15, 15);
    char *string = new char[50];

    sprintf(string, "FPS: %d", fps);

    int len, i;
    len = strlen(string);
    glColor3f(0.0f, 1.0f, 1.0f);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
    resetPerspectiveProjection();
    glColor3f(1, 1, 1);
    glPopMatrix();
}