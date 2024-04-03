#include "models.h"


 /* Author: Depanshu and Kevin*/
bool check_player_inside_triangle(Game_Object *player, Game_Object *object);

/*******************************************************************************
 * Purpose: Initializes a game object with specified location, type, and default
 *            dimensions. Vertices are assigned based on the object type
 *
 * Input: -x and y coordinates for the top left vertex's of the object
 *        -A pointer to the Game_Object struct;
 *        -Game_Object_Type specifying the object type.
 *
 * Output: Game_Object struct initialized with specified position, type,
 *          and default dimensions.
 *
 * Restriction:
 *        - Expects the user to give correct x and y coordinates
*******************************************************************************/
void initialize_game_object(int x, int y, Game_Object * object,
                            Game_Object_Type type) {
	
/* Initialize the top left vertex and bottom right vertex, same for all obj*/
     object->top_left.x_pos = x;
     object->top_left.y_pos = y;
     object->bottom_right.x_pos = x + DEFAULT_OBJECT_WIDTH;
     object->bottom_right.y_pos = y + DEFAULT_OBJECT_HEIGHT;

     /* Adjust the bottom vertices based on the object type */
     object->bottom_left.x_pos = x;
	 object->bottom_right.x_pos = x + DEFAULT_OBJECT_WIDTH;
     object->bottom_left.y_pos = (type == PLATFORM_SHORT) ?
             (y + SHORT_OBJECT_HEIGHT) : (y + DEFAULT_OBJECT_HEIGHT);
	 object->bottom_right.y_pos = (type == PLATFORM_SHORT) ?
             (y + SHORT_OBJECT_HEIGHT) : (y + DEFAULT_OBJECT_HEIGHT);


     /* Adjust the top right vertex's x position for a triangle */
     object->top_right.y_pos = y; /*y is the same for all*/
     object->top_right.x_pos = (type == TRIANGLE) ?
             (x + TRIANGLE_BASE_WIDTH) : (x + DEFAULT_OBJECT_WIDTH);

     /*all objects expect player will have the same velocity*/
     object->object_velocity = (type == PLAYER) ? 0 : DEFAULT_OBJECT_VELOCITY;
     object->type = type;

     if(type == PLAYER) {
         object->state= PLAYER_STATE_ON_GROUND;
     } else {
         object->state = OBJECT_RIGHT_OFF_PLAYER;
     }

}


/*******************************************************************************
 * Purpose:  Sets the y position of the ground
 *
 * Input:  y coordinate for ground position; pointer to the Ground struct.
 * Output: Ground struct initialized at specified y position.
*******************************************************************************/
void initialize_ground(Ground* ptr_ground) {
	ptr_ground->y_pos = GROUND_POS;
}


/*******************************************************************************
 * Purpose: Checks for fatal collisions between the player and game objects
 *          in the game model.
 * 
 * Details: Iterates through game objects to detect collisions. For platforms,
 *          checks for vertical overlap excluding the top edge. For triangles,
 *          uses a separate function to check if any of the player vertices'
 *          is inside the traingle.
 * 
 * Input: 
 *        - model: Pointer to the Model struct with game state and objects.
 *
 * Output: 
 *        - Returns TRUE if a fatal collision with nearby objects is detected,
 *          otherwise FALSE.
 *
 * Assumptions:
 *        - Player is the first object in the game_objects array.
 *        - Only Objects near the player require collision checks.
*******************************************************************************/

bool player_fatal_collision(Model *model) {
    Game_Object * player = &(model->game_objects[PLAYER_INDEX]);
	Game_Object *object;
    short i= PLAYER_INDEX + 1;
    bool fatal_collision_detected = FALSE;

    for(i; i< model->num_active_objects; i++) {
		object = &(model->game_objects[i]);

        /*Skip if object not near or no vertical overlap */
        if (object->state != OBJECT_NEAR_PLAYER ||
            player->top_left.y_pos > object->bottom_left.y_pos ||
            player->bottom_left.y_pos < object->top_left.y_pos)  continue;


        if (object->type == TRIANGLE &&
            check_player_inside_triangle(player, object)) {
            fatal_collision_detected = TRUE;
        }

        /* Check vertical overlap, exclude top edge. */
        if (object->type != TRIANGLE && 
            player->bottom_left.y_pos > object->top_left.y_pos) {      
            fatal_collision_detected = TRUE;
        }

    }
    return fatal_collision_detected;
}



/*******************************************************************************
 * Checks if any player corner is inside a triangle object.
 * 
 * Inputs:
 * - player: Pointer to the player's Game_Object.
 * - object: Pointer to a triangle Game_Object.
 * 
 * Returns TRUE if any player corner intersects the triangle, else FALSE.
*******************************************************************************/
bool check_player_inside_triangle(Game_Object *player, Game_Object *object) {
    return point_inside_triangle(&(player->bottom_left), object) ||
           point_inside_triangle(&(player->bottom_right), object) ||
           point_inside_triangle(&(player->top_left), object) ||
           point_inside_triangle(&(player->top_right), object);
}





/*******************************************************************************
 * Purpose: Checks if a point(Vertex) is inside a triangle.
 *
 * Input: Pointer to Vertex (point) and Triangle structs.
 * Output: TRUE if point is inside triangle, FALSE otherwise.
 *
 * Details: Determines if the point lies within the left or right half of the triangle
 * 			based on its hypotenuse.
 *
 * Collision Detection Logic:
 * 1. Initially checks if the point is with the y axis bounds of the triangle
 * 2. The triangle is conceptually split into two halves at its midpoint
 * 3. Left half check: A hypothetical Y-coordinate on the hypotenuse
 *    from the bottom left vertex is calculated. If the point's Y
 *    is below this, it's inside the left half.
 * 4. Right half check: Similarly, a Y-coordinate on the hypotenuse from
 *     the top vertex determines if the point is inside the right half.
 * 5. A point is outside triangle if it does not meet either of the condition
 *
*******************************************************************************/
bool point_inside_triangle(Vertex* point, Game_Object *triangle) {

    int y_on_hypotenuse_from_bot_left, y_on_hypotenuse_from_top;
    int point_x_pos = point->x_pos , point_y_pos = point->y_pos;
    bool is_inside = FALSE;


    if(point_y_pos >= triangle->top_right.y_pos &&
        point_y_pos <= triangle->bottom_left.y_pos) {


        /* Check if the point is within the left half of the triangle */
        if(point_x_pos >= triangle->bottom_left.x_pos &&
           point_x_pos <= triangle->top_right.x_pos) {

            if (Y_ON_HYPOTENUSE_FROM_BOT_LEFT(point_x_pos, triangle) <= point_y_pos) {
                is_inside = TRUE; /*point is inside left half of the triangle*/
            }

        }

        /* Check if the point is within the right half of the triangle */
        if(point_x_pos >= triangle->top_right.x_pos  &&
           point_x_pos<= triangle->bottom_right.x_pos) {
            
            if(Y_ON_HYPOTENUSE_FROM_TOP(point_x_pos, triangle) <= point_y_pos) {
                is_inside = TRUE;/*point is inside right half of the triangle */
            }

        }
    }
    return is_inside;
}

