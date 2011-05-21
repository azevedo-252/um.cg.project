/**
 * Define uma class que reperesenta uma Arvore
 */
#ifndef _tree_h
#define _tree_h

#include "Textures.h"
#include "Vertex.h"

class Tree {
public:
    Tree();
    void set_pos(Vertex* new_coords);
    void render();
    
private:
    TexData tex_tree;
    Vertex* coords;
    
    void drawTree();
};

#endif