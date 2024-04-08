#ifndef MODELS_H
#define MODELS_H

typedef unsigned int bool;
#define FALSE 0
#define TRUE 1



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
	bool fatal_collision;
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
	short hor_vel;
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



typedef struct
{
	Vertex top_left;
} Victory_Wall;


/* Contains all the relevant structure which will be used in the game*/
typedef struct {
	Player player[2];
    short num_active_players;
	Triangle triangles[10];
	short num_active_triangles;
	Ground ground;
	Platform platform[10];
	short num_active_platforms;
	Victory_Wall victory_wall;
    bool victory_wall_active;

} Model;



/*--------------Functions------------------*/


void update_player_pos(Player * player);
void update_triangle_pos(Triangle* triangle);
void update_platform_pos(Platform* platform);

void initialize_player(int x, int y, Player* player);
void initialize_triangle(int x, int y, short hor_vel, Triangle * triangle);
void initialize_platform(int x, int y, int width, int height, int hor_vel, Platform * platform);
void initialize_ground(int y, Ground* ground);


bool player_safe_on_ground_or_surface(Model *model, short player_num);
bool platform_collision_safe(Player* player, Platform* platform);
bool ground_collision(Player* player, Ground* ground);


bool player_fatal_collision(Model *model, short player_num);
bool has_player_collided_with_any_triangle(Model *model, short player_num);
bool has_player_collided_with_any_platform(Model *model, short player_num);
bool platform_collision_unsafe(Player* player, Platform* platform);
bool player_triangle_collision( Player* player , Triangle * triangle);
bool player_triangle_collision_helper( Player* player , Triangle * triangle);


bool victory_collision(Player* player, Victory_Wall* victory_wall);

#endif