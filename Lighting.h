/* 
 * File:   Lighting.h
 * Author: naps62
 *
 * Created on May 18, 2011, 1:37 AM
 */

#ifndef _LIGHTING_H
#define	_LIGHTING_H

#include <GL/glut.h>

class Lighting {
	
public:
	float pos[4];
	GLfloat amb[3];
	GLfloat diff[3];
	GLfloat spec[4];
	
	Lighting();
	virtual ~Lighting();
	
	void render();
	
	
private:

};

#endif	/* _LIGHTING_H */

