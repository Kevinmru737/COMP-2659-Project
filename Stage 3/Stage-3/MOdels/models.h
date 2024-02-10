#include "types.h"
typedef struct 
{
	int x_pos, y_pos, vert_vel;
	bool is_jumping;
} Player;


typedef struct 
{
	int x_pos, y_pos, hor_vel;
} Triangle;

typedef struct 
{
	int y_pos;
} Ground;

typedef struct 
{
	int y_pos, x_pos, hor_vel;
} Platform;

