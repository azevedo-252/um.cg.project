/* 
 * File:   Profiling.h
 * Author: gabriel
 *
 * Created on May 18, 2011, 1:01 AM
 */

#ifndef PROFILING_H
#define	PROFILING_H

typedef enum enum_times {
	TIME_STARTUP,
	TIME_RENDER_TOTAL,
	TIME_RENDER_TREES,
	TIME_SIZE
} TIMES;


#include "Vertex.h"

class Profiling {
public:
	Profiling();
	void update();
	void render();
	void print(char *string);
	void print_fps();
	void reset_time();
	void start_time(TIMES num, char* name);
	void end_time(TIMES num);
	void print_time();
private:
	int start[TIME_SIZE];
	int end[TIME_SIZE];
	char* name[TIME_SIZE];

	bool printed;
	Vertex *coords;
	float start_coord_y;
	float old_count, new_count;
	int frames, fps;
};

#endif	/* PROFILING_H */

