/* 
 * File:   Profiling.h
 * Author: gabriel
 *
 * Created on May 18, 2011, 1:01 AM
 */

#ifndef PROFILING_H
#define	PROFILING_H

class Profiling {
public:
    Profiling();
    void update();
    void render();
private:
    float old_count, new_count;
    int frames, fps;
    void setOrthographicProjection();
    void resetPerspectiveProjection();
};

#endif	/* PROFILING_H */

