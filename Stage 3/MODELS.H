#ifndef MODELS_H
#define MODELS_H

#include "types.h"
#define OBSTACLE_VELOCITY 3


/* Represents a single vertex of a polygon*/
typedef struct 
{
	int x_pos, y_pos;
}Vertex;



/* The four vertices define the player square. 
The player is fixed in its horizontal position but can move in the vertical direction.
The top_left vertex is considered the hotspot.
*/
typedef struct 
{
	Vertex top_left, top_right, bot_left, bot_right;
	int vert_vel;
	bool is_jumping;
} Player;




/*The triangle can be thought of as two diagonal lines with a slope of 2 and 
* a horizontal line. The slope of these lines will be used to determine
* whether a collision has occurred between the player and the triangle.
* The triangle is represented using its three vertices ( bot.left, top and bot.right).
*/
typedef struct 
{	
	Vertex hot_spot;
	Vertex bot_left, top, bot_right;
	int hor_vel;
} Triangle;



/*Will be static, the player is safe whenever in contact with this */
typedef struct 
{
	int y_pos;
} Ground;



/*A single platfrom that the player can "glide" on.
  Only the top edge is safe for collision*/
typedef struct 
{	
	Vertex top_left, top_right, bot_left, bot_right;
	int hor_vel;
} Platform;


/* Keeps track of the score as well as a position for printing to the screen */
typedef struct
{
	Vertex top_left;
	int attempt_number;
} Attempt;

typedef struct
{
	Vertex top_left;
} Victory_Wall;



/*--------------Functions------------------*/

void jump(Player * player);
void move_player(Player * player);
void stop_jump(Player * player);
void move_triangle(Triangle* triangle);
void move_platform(Platform* platform);

void initialize_player(int x, int y, Player* player);
void initialize_triangle(int x, int y, int hor_vel, Triangle * triangle);
void initialize_platform(int x, int y, int width, int height, int hor_vel, Platform * platform);
void initialize_ground(int y, Ground* ground);

#endif