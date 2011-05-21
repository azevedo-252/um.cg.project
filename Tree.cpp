#include <GL/glew.h>

#include "Tree.h"
#include "externs.h"

Tree::Tree() {
	coords = new Vertex(0, 0, 0);
}

void Tree::set_pos(Vertex* new_coords) {
	coords->x = new_coords->x;
	coords->y = new_coords->y;
	coords->z = new_coords->z;
}

//void Tree::render(GLuint treeList) {
//}

void Tree::drawTree(int tex_id) {

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glNormal3f(0, 0, -1);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(30, 50, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(30, -2, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-30, -2, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-30, 50, 0);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}