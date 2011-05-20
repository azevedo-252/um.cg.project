/* 
 * File:   Lifes.cpp
 * Author: gabriel
 * 
 * Created on May 20, 2011, 12:48 AM
 */

#include <GL/glew.h>

#include "Lifes.h"
#include "externs.h"
#include "ChangeMode.h"

Lifes::Lifes() {
    lifes = conf.rint("player:lifes");
	hasEnded = false;
    image = Textures::get(LIFES);
}

void Lifes::drawLife() {
    glBindTexture(GL_TEXTURE_2D, image.gl_id);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(50, 50);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0, 50);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(50, 0);

    glEnd();
}

void Lifes::render() {
    ChangeMode::setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(g_win_w / 2, 10, 0);

    for (int i = 0; i < lifes; i++) {
        drawLife();
        glTranslatef(55, 0, 0);
    }

    //    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    ChangeMode::resetPerspectiveProjection();
}

