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
	
	Trees();
	void render();

private:

};

#endif