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

	mat_amb[0] = conf.rfloat("trees:amb_r");
	mat_amb[1] = conf.rfloat("trees:amb_g");
	mat_amb[2] = conf.rfloat("trees:amb_b");
	mat_amb[3] = conf.rfloat("trees:amb_w");

	mat_diff[0] = conf.rfloat("trees:diff_r");
	mat_diff[1] = conf.rfloat("trees:diff_g");
	mat_diff[2] = conf.rfloat("trees:diff_b");
	mat_diff[3] = conf.rfloat("trees:diff_w");

	mat_spec[0] = conf.rfloat("trees:spec_r");
	mat_spec[1] = conf.rfloat("trees:spec_g");
	mat_spec[2] = conf.rfloat("trees:spec_b");
	mat_spec[3] = conf.rfloat("trees:spec_w");

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
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);

	g_profiling->start_time(TIME_RENDER_TREES, "Tree Render");
	
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0);
	glCallList(treesList);
	glBlendFunc(GL_ONE, GL_ZERO);
	glAlphaFunc(GL_ALWAYS, 0);
	glEnable(GL_CULL_FACE);
	
	g_profiling->end_time(TIME_RENDER_TREES);

	//    for (int i = 0; i < num_trees; i++) {
	//        trees[i]->render();
	//    }
}