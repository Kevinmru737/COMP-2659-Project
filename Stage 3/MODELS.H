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
*/
typedef struct 
{	
	int const slope;
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
{	Vertex top_left, top_right;
	int hor_vel;
} Platform;

