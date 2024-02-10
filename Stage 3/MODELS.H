#include "types.h"


/* Represents a single vertex of a polygon*/
typedef struct 
{
	int x_pos, y_pos;
}Vertex;



/* The four vertices define the player square. 
The player is fixed in its horizontal position but can move in the vertical direction.
*/
typedef struct 
{
	Vertex top_left, top_right, bot_left,bot_right;
	int vert_vel;
	bool is_jumping;
} Player;




/*The triangle can be thought of as two diagnol lines with a slope
  a horizontal line. The slope of these lines will be used to determine
  whether a collision has occurred between the player and the triangle.
  The triangle is represented using its three vertices ( bot.left ,top and right).
  All triangles will be right angled
*/
typedef struct 
{	
	int slope;
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
{	Vertex top_left, top_right, bot_left, bot_right;
	int hor_vel;
} Platform;




/*--------------Funcitons------------------*/

void jump(Player * player);
void move_player(Player * player);
void stop_jump(Player * player);
void move_triangle_obs(Triangle* triangle);
void move_platform_(Platform* platform);

Player* create_player(int x, int y );
Triangle* create_triangle(int x, int y, int hor_vel);
Platform* create_platform(int x_top_left, int y_top_left, int width, int height, int hor_vel);
