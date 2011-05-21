#include "Trees.h"
#include "GLManager.h"

#include "externs.h"

Trees::Trees() {
	num_trees = conf.rint("game:num_trees");
	
	trees = (Tree **) calloc(num_trees, sizeof (Tree *));
	
	for ( int i = 0 ; i < num_trees ; i++ ) {
		trees[i] = new Tree();
		Vertex* pos = NULL;
		
	    pos = GLManager::randomVertex();
        g_map->adjustPlayableCoords(pos);
        
        pos->y = g_map->triangulateHeight(pos->x, pos->z);
        trees[i]->set_pos(pos);
	}
}

void Trees::render(){
    for (int i = 0; i < num_trees; i++) {
        trees[i]->render();
    }
}