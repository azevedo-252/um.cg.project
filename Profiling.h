/* 
 * File:   Profiling.h
 * Author: gabriel
 *
 * Created on May 18, 2011, 1:01 AM
 */

#ifndef PROFILING_H
#define	PROFILING_H

#define TIME_SIZE 10

#include "Vertex.h"

class Profiling {
public:
    Profiling();
    void update();
    void render();
    void print(char *string);    
    void print_fps();
    void reset_time();
    void start_time(int num, char* name);
    void end_time(int num);
    void print_time();
private:
    float start[TIME_SIZE];
    float end[TIME_SIZE];
    char* name[TIME_SIZE];
    
    Vertex *coords;
    float old_count, new_count;
    int frames, fps;
};

#endif	/* PROFILING_H */

