#include <GL/glew.h>

#include "Trees.h"
#include "GLManager.h"

#include "externs.h"

Trees::Trees() {
	num_trees = conf.rint("game:num_trees");

	trees = (Tree **) calloc(num_trees, sizeof (Tree *));

	for (int i = 0; i < num_trees; i++) {
		trees[i] = new Tree();
		Vertex* pos = NULL;

		pos = GLManager::randomVertex();
		g_map->adjustPlayableCoords(pos);

		pos->y = g_map->triangulateHeight(pos->x, pos->z);
		trees[i]->set_pos(pos);
	}

	tex_tree = Textures::get(TREE);
	createTreesList();
}

void Trees::createTreesList() {
	
	//gera a lista para uma arvore
	treeList = glGenLists(1);
	glNewList(treeList, GL_COMPILE);
	Tree::drawTree(tex_tree.gl_id);
	glEndList();

	//gera a lista para todas as arvores, com base na lista anterior
	treesList = glGenLists(1);
	glNewList(treesList, GL_COMPILE);
	for (int i = 0; i < num_trees; i++) {
		glPushMatrix();
		glTranslatef(trees[i]->coords->x, trees[i]->coords->y, trees[i]->coords->z);
		glCallList(treeList);
		glRotatef(90, 0, 1, 0);
		glCallList(treeList);
		glPopMatrix();
	}
	glEndList();
	
}

void Trees::render() {
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0);
	glCallList(treesList);
	glBlendFunc(GL_ONE, GL_ZERO);
	glAlphaFunc(GL_ALWAYS, 0);
	glEnable(GL_CULL_FACE);

	//    for (int i = 0; i < num_trees; i++) {
	//        trees[i]->render();
	//    }
}