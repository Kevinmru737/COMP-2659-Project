#ifndef MODELS_H
#define MODELS_H


#include "consts.h"
/*******************************************************************************
 * Purpose: Defines the states for game objects, including the player and obstacles.
 *
 * Enum Values:
 * - OBJECT_RIGHT_OFF_PLAYER: Object is right of the player.
 * - OBJECT_NEAR_PLAYER: Object is near the player.
 * - OBJECT_LEFT_OFF_PLAYER: Object is left of the player.
 * - PLAYER_STATE_ON_GROUND: Player or object is on the ground.
 * - PLAYER_STATE_MOVING_UP: Player or object is moving up.
 * - PLAYER_STATE_ON_PLATFORM: Player or object is on a platform.
 * - PLAYER_STATE_MOVING_DOWN: Player or object is moving down.
*******************************************************************************/
typedef enum {
    OBJECT_RIGHT_OFF_PLAYER,
    OBJECT_NEAR_PLAYER,
    OBJECT_LEFT_OFF_PLAYER,
    PLAYER_STATE_ON_GROUND,
    PLAYER_STATE_MOVING_UP,
    PLAYER_STATE_ON_PLATFORM,
    PLAYER_STATE_MOVING_DOWN
} States;



/*******************************************************************************
 * * Purpose:Defines the types of game objects present in the game.
 *
 * Enum Values:
 * - PLAYER: Represents a player character.
 * - TRIANGLE: Represents a triangular obstacle
 * - PLATFORM_BRICK_1: Represents a type of brick platform
 * - PLATFORM_BRICK_2: Represents another of brick platform
 * - PLATFORM_1: Represents a platform.
 * - PLATFORM_SHORT: Represents a shorter variant of a platform.
*******************************************************************************/
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

/*******************************************************************************
 * Purpose: Represents a game object within the game. Each game object is
 *          defined by its geometric vertices and type, along with states
 *          that it can reach.
 *
 * Fields:
 * - top_left, bottom_left, top_right, bottom_right: Vertices defining the
 *                                                   shape of the game object.
 *
 * - type: A Game_Object_Type enum value specifying the type of the game object.
 *
 * - object_state: An enum value representing the current state of
 *                   the game object.
 *
 * - object_velocity: A short value representing velocity of the game object,
 *                    can be in the horizontal or vertical direction
 *
*******************************************************************************/
typedef struct {
    Vertex top_left, bottom_left, top_right, bottom_right;
    Game_Object_Type type;
    States state;
    short object_velocity;
} Game_Object;

/*******************************************************************************
 * Purpose: Represents the static ground in the game
 * Fields:
 * - y_pos: The Y-axis position of the ground
*******************************************************************************/

typedef struct {
    unsigned int y_pos;
} Ground;

/*******************************************************************************
 * Purpose: Aggregates all game entities.
 * Fields:
 * - game_objects: Array of game objects. There is max number of game objects-20
 * - num_active_objects: Count of active game objects.
 * - ground: The ground entity of the game.
*******************************************************************************/
typedef struct {
    Game_Object game_objects[20]; /**/
    short num_active_objects;
	Ground ground;
} Model;



/*--------------Functions------------------*/
void initialize_game_object(int x, int y, Game_Object * object, Game_Object_Type type);
void initialize_ground(Ground* ground);
bool player_fatal_collision(Model *model);
bool point_inside_triangle(Vertex* point, Game_Object *triangle);

#endif