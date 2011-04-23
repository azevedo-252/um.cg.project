/* 
 * File:   SkyBox.cpp
 * Author: gabriel
 * 
 * Created on 16 de Abril de 2011, 22:53
 */
#include "externs.h"
#include "SkyBox.h"
#include "Vertex.h"

SkyBox::SkyBox() {
    face1 = Textures::get(SKYBOX1);
    face2 = Textures::get(SKYBOX2);
    face3 = Textures::get(SKYBOX3);
    face4 = Textures::get(SKYBOX4);
    face5 = Textures::get(SKYBOX5);
    face6 = Textures::get(SKYBOX6);
}

void SkyBox::render() {
    Vertex *position = g_player->coords;
    int sizeBox = sqrt(2 * pow(10000, 2)) / 2 - 1500;
    Vertex *size = new Vertex(sizeBox, sizeBox, sizeBox);

    // Begin DrawSkybox
    glColor4f(1.0, 1.0, 1.0, 1.0f);

    // Save Current Matrix
    glPushMatrix();

    // Second Move the render space to the correct position (Translate)
    glTranslatef(position->x, position->y + 100, position->z);
    glRotatef(90, 1, 0, 0);
    // First apply scale matrix
    glScalef(size->x, size->y, size->z);

    float cz = -0.0f, cx = 1.0f;
    float r = 1.004f; // If you have border issues change this to 1.005f
    // Common Axis Z - FRONT Side CIMA
    glBindTexture(GL_TEXTURE_2D, face2.gl_id);
    glBegin(GL_QUADS);
    //    glTexCoord2f(cx, cz);
    //    glVertex3f(-r, 1.0f, -r);
    //    glTexCoord2f(cx, cx);
    //    glVertex3f(-r, 1.0f, r);
    //    glTexCoord2f(cz, cx);
    //    glVertex3f(r, 1.0f, r);
    //    glTexCoord2f(cz, cz);
    //    glVertex3f(r, 1.0f, -r);
    glTexCoord2f(cz, cz);
    glVertex3f(r, 1.0f, -r);

    glTexCoord2f(cz, cx);
    glVertex3f(r, 1.0f, r);

    glTexCoord2f(cx, cx);
    glVertex3f(-r, 1.0f, r);

    glTexCoord2f(cx, cz);
    glVertex3f(-r, 1.0f, -r);



    glEnd();

    //    // Common Axis Z - BACK side BAIXO
    glBindTexture(GL_TEXTURE_2D, face1.gl_id);
    glBegin(GL_QUADS);
    glTexCoord2f(cx, cz);
    glVertex3f(-r, -1.0f, -r);
    glTexCoord2f(cx, cx);
    glVertex3f(-r, -1.0f, r);
    glTexCoord2f(cz, cx);
    glVertex3f(r, -1.0f, r);
    glTexCoord2f(cz, cz);
    glVertex3f(r, -1.0f, -r);
    glEnd();
    //
    //    // Common Axis X - Left side TRAS

    glBindTexture(GL_TEXTURE_2D, face6.gl_id);
    glBegin(GL_QUADS);
    glTexCoord2f(cx, cz);
    glVertex3f(-1.0f, -r, -r);
    glTexCoord2f(cz, cz);
    glVertex3f(-1.0f, r, -r);
    glTexCoord2f(cz, cx);
    glVertex3f(-1.0f, r, r);
    glTexCoord2f(cx, cx);
    glVertex3f(-1.0f, -r, r);



    glEnd();
    //
    //    // Common Axis X - Right side
    glBindTexture(GL_TEXTURE_2D, face5.gl_id);
    glBegin(GL_QUADS);
    glTexCoord2f(cx, cx);
    glVertex3f(1.0f, -r, r);
    glTexCoord2f(cz, cx);
    glVertex3f(1.0f, r, r);
    glTexCoord2f(cz, cz);
    glVertex3f(1.0f, r, -r);
    glTexCoord2f(cx, cz);
    glVertex3f(1.0f, -r, -r);
    glEnd();
    //
    //    // Common Axis Y - Draw Up side
//    glBindTexture(GL_TEXTURE_2D, face3.gl_id);
//    glBegin(GL_QUADS);
//    glTexCoord2f(cz, cx);
//    glVertex3f(-r, -r, 1.0f);
//    glTexCoord2f(cx, cx);
//    glVertex3f(-r, r, 1.0f);
//    glTexCoord2f(cx, cz);
//    glVertex3f(r, r, 1.0f);
//    glTexCoord2f(cz, cz);
//    glVertex3f(r, -r, 1.0f);
//
//    glEnd();
    //
    //    // Common Axis Y - Down side CIMA
    glBindTexture(GL_TEXTURE_2D, face4.gl_id);
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(cz, cz);
    glVertex3f(r, -r, -1.0f);
    glTexCoord2f(cx, cz);
    glVertex3f(r, r, -1.0f);
    
    glTexCoord2f(cx, cx);
    glVertex3f(-r, r, -1.0f);
    glTexCoord2f(cz, cx);
    glVertex3f(-r, -r, -1.0f);
    glEnd();

    // Load Saved Matrix
    glPopMatrix();

}