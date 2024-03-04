#ifndef MODELS_H
#define MODELS_H

#include "bool.h"
#define TRIANGLE_BASE_WIDTH 15
#define DEFAULT_OBJECT_WIDTH 31
#define DEFAULT_OBJECT_HEIGHT 31
#define SHORT_OBJECT_HEIGHT 15
#define DEFAULT_OBJECT_VELOCITY 5
#define GROUND_POS 271



typedef enum {
    OBJECT_RIGHT_OFF_PLAYER,
    OBJECT_NEAR_PLAYER,
    OBJECT_LEFT_OFF_PLAYER,
    PLAYER_STATE_ON_GROUND,
    PLAYER_STATE_MOVING_UP,
    PLAYER_STATE_ON_PLATFORM,
    PLAYER_STATE_MOVING_DOWN
} States;



/***************************************************
 * Purpose:Defines the types of game objects present in the game.
 *
 * Enum Values:
 * - PLAYER: Represents a player character.
 * - TRIANGLE: Represents a triangular obstacle
 * - PLATFORM_BRICK_1: Represents a type of brick platform
 * - PLATFORM_BRICK_2: Represents another of brick platform
 * - PLATFORM_1: Represents a platform.
 * - PLATFORM_SHORT: Represents a shorter variant of a platform.
 ***************************************************/
typedef enum {
    PLAYER,
    TRIANGLE,
    PLATFORM_BRICK_1,
    PLATFORM_BRICK_2,
    PLATFORM_1,
    PLATFORM_SHORT
} Game_Object_Type;



/* Purpose: Represents a single vertex of a Game_Object*/
typedef struct
{
    int x_pos, y_pos;
}Vertex;

/***************************************************
 * Purpose: Represents a game object within the game. Each game object is defined
 *          by its geometric vertices and type, along with states that it can reach.
 *
 * Fields:
 * - top_left, bottom_left, top_right, bottom_right: Vertices defining the shape of the game object.
 *
 * - type: A Game_Object_Type enum value specifying the type of the game object.
 *
 * - object_state: An enum value representing the current state of
 *                   the game object.
 * - object_velocity: A short value representing velocity of the game object, can be in the horizontal or vertical direction
 *
 ***************************************************/
typedef struct {
    Vertex top_left, bottom_left, top_right, bottom_right;
    Game_Object_Type type;
    States state;
    short object_velocity;
} Game_Object;

typedef struct {
    unsigned int y_pos;
} Ground;

/* Contains all the relevant structure which will be used in the game*/
typedef struct {
    Game_Object game_objects[10];
    short num_active_objects;
	Ground ground;
} Model;



/*--------------Functions------------------*/

void initialize_game_object(int x, int y, Game_Object * object, Game_Object_Type type);
void initialize_ground(Ground* ground);

bool platform_collision_unsafe(Model *model, short player_num);

bool fatal_collision(Model *model, short player_num);

bool point_inside_triangle(Vertex* point, Game_Object *triangle);

bool player_triangle_collision( Model *model, short player_num);

#endif