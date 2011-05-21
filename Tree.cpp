#include <GL/glew.h>

#include "Tree.h"
#include "externs.h"

Tree::Tree() {
	tex_tree = Textures::get(TREE);
	coords = new Vertex(0, 0, 0);
}

void Tree::set_pos(Vertex* new_coords) {
    coords->x = new_coords->x;
    coords->y = new_coords->y;
    coords->z = new_coords->z;
}

void Tree::drawTree(){
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, tex_tree.gl_id);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(30, 50, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(30, -2, 0);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-30, -2, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-30, 50, 0);

    glEnd();
    
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 50, 30);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, -2, 30);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0, -2, -30);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0, 50, -30);

    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Tree::render(){
	glPushMatrix();
		glTranslatef(coords->x, coords->y, coords->z);
		drawTree();
	glPopMatrix();
}