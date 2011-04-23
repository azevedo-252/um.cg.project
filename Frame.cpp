/* 
 * File:   Timer.cpp
 * Author: gabriel
 * 
 * Created on 9 de Abril de 2011, 18:34
 */

#include "Frame.h"

Frame::Frame() {
    this->current_anim = MOVE_NONE;
    this->current_frame = 0;
}

void Frame::add_anim(MOVE_TYPE type, int start, int end) {
	frames[type].start = start;
	frames[type].end = end;
}

void Frame::set_anim(MOVE_TYPE anim) {
    this->current_anim = anim;
    this->current_frame = frames[this->current_anim].start;
}

MOVE_TYPE Frame::get_anim() {
	return current_anim;
}

int Frame::get_frame() {
    return current_frame;
}
void Frame::inc_frame() {
    if (current_frame == frames[current_anim].end)
    	current_frame = frames[current_anim].start;
    else
        current_frame++;
}



