/* 
 * File:   ChangeMode.cpp
 * Author: gabriel
 * 
 * Created on May 19, 2011, 10:34 PM
 */

#include "externs.h"
#include "ChangeMode.h"


namespace ChangeMode {

    void setOrthographicProjection() {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, g_win_w, 0, g_win_h);
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_LIGHTING);
    }

    void resetPerspectiveProjection() {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_LIGHTING);
    }

}

