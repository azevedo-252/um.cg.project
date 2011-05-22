/**
 * Define uma class que reperesenta uma Arvores
 */
#ifndef _trees_h
#define _trees_h

#include "Tree.h"

class Trees {
public:
    int num_trees;
    Tree** trees;
    GLuint treeList;
    GLuint treesList;
	
	GLfloat mat_amb[4];
	GLfloat mat_diff[4];
	GLfloat mat_spec[4];

    Trees();
    void createTreesList();
    void render();

private:

};

#endif