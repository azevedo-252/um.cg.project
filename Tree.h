/**
 * Define uma class que reperesenta uma Arvore
 */
#ifndef _tree_h
#define _tree_h

#include "Textures.h"
#include "Vertex.h"

class Tree {
public:
    Vertex* coords;
    
    Tree();
    void set_pos(Vertex* new_coords);
    //void render();
    static void drawTree(int tex_id);
    
};

#endif