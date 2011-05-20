/* 
 * File:   Lifes.h
 * Author: gabriel
 *
 * Created on May 20, 2011, 12:48 AM
 */

#ifndef LIFES_H
#define	LIFES_H

#include "Textures.h"

class Lifes {
public:
    int lifes;
    Lifes();
    void render();
private:
    void drawLife();
    TexData image;
};

#endif	/* LIFES_H */

