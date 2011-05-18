/* 
 * File:   Frame.h
 * Author: gabriel
 *
 * Created on 9 de Abril de 2011, 18:34
 */

#ifndef Frame_H
#define	Frame_H

typedef enum e_move_type {
	MOVE_NONE,
	MOVE_WALK,
	MOVE_JUMP,

	MOVE_COUNT,
} MOVE_TYPE;

typedef struct s_anim {
	int start;
	int end;
} ANIM;

class Frame {
public:
	int walk_frames;
	ANIM frames[MOVE_COUNT];

	MOVE_TYPE current_anim;
	int current_frame;

	Frame();
	void add_anim(MOVE_TYPE type, int start, int count);
	void set_anim(MOVE_TYPE anim);
	MOVE_TYPE get_anim();
	int get_frame();
	void inc_frame();
private:

};

#endif	/* Frame_H */

