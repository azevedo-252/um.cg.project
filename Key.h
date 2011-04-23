/* 
 * File:   Key.h
 * Author: gabriel
 *
 * Created on 9 de Abril de 2011, 17:42
 */

#ifndef KEY_H
#define	KEY_H

#include "Model_MD2.h"
#include "Vertex.h"

class Key : public Model_MD2 {
public:
    float dir_dist;
    bool catched;

    Key(const std::string &path);
    void set_pos(Vertex *new_coords);
    void render();
    void update();
};

#endif	/* KEY_H */

