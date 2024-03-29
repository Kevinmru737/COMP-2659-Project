#include "models.h"


 /* Author: Depanshu and Kevin*/


/*********************************************************
 * Purpose: Initializes a game object with specified location, type, and default dimensions.
 *          Vertices are assigned based on the object type
 *
 * Input: x and y coordinates for the top left vertex's of the object;
 *        a pointer to the Game_Object struct; Game_Object_Type specifying the object type.
 * Output: Game_Object struct initialized with specified position, type, and default dimensions.
 *
 * Restriction:
 *        - No bounds checking is performed, so the user must provide valid parameters.
 *
 *********************************************************/
void initialize_game_object(int x, int y, Game_Object * object, Game_Object_Type type) {
	
     /* Initialize the top left vertex and bottom right vertex, same for all objects*/
     object->top_left.x_pos = x;
     object->top_left.y_pos = y;
     object->bottom_right.x_pos = x + DEFAULT_OBJECT_WIDTH;
     object->bottom_right.y_pos = y + DEFAULT_OBJECT_HEIGHT;

     /* Adjust the bottom vertices based on the object type */
     object->bottom_left.x_pos = x;
	 object->bottom_right.x_pos = x + DEFAULT_OBJECT_WIDTH;
     object->bottom_left.y_pos = (type == PLATFORM_SHORT) ? (y + SHORT_OBJECT_HEIGHT) : (y + DEFAULT_OBJECT_HEIGHT);
	 object->bottom_right.y_pos =(type == PLATFORM_SHORT) ? (y + SHORT_OBJECT_HEIGHT) : (y + DEFAULT_OBJECT_HEIGHT);
	 
	 
	 
     /* Adjust the top right vertex's x position for a triangle */
     object->top_right.y_pos = y;
     object->top_right.x_pos = (type == TRIANGLE) ? (x + TRIANGLE_BASE_WIDTH) : (x + DEFAULT_OBJECT_WIDTH);

     object->object_velocity = (type == PLAYER) ? 0 : DEFAULT_OBJECT_VELOCITY;

     object->type = type;

     if(type == PLAYER) {
         object->state= PLAYER_STATE_ON_GROUND;
     } else {
         object->state = OBJECT_RIGHT_OFF_PLAYER;

     }

}



/*********************************************************
 * Purpose:  Sets the y position of the ground
 *
 * Input:  y coordinate for ground position; pointer to the Ground struct.
 * Output: Ground struct initialized at specified y position.
 *
 * Restriction:
 *		  - No bounds checking is done so, user has to give valid parameters
 *
 *********************************************************/
void initialize_ground(Ground* ptr_ground) {
	ptr_ground->y_pos = GROUND_POS;
}



/*********************************************************
 * Purpose: Checks for fatal collisions between the player and game objects (triangles and platforms) in the game model.
 * 
 * Details: A collision with platforms is detected through vertical overlap, while for triangles,
 *		   checking any player's corner inside the triangle indicates a collision. 
 *
 * Input: 
 *        - model: Pointer to the Model struct, containing game state and objects.
 *        - player_num: Index of the player in the model's game_objects array.
 *
 * Output: 
 *        - Returns TRUE if a fatal collision is detected with any object marked as near the player, else FALSE.
 *
 * Assumptions:
 *        - The first object in the game_objects array is the player.
 *

 *********************************************************/
bool player_fatal_collision(Model *model, short player_num) {
    Game_Object * player = &(model->game_objects[player_num]);
	Game_Object *object;
    short i= PLAYER_INDEX + 1;

    for(i; i< model->num_active_objects; i++) {
		object = &(model->game_objects[i]);
		
		
		/*Skip if the object is not near the player or if there's no vertical overlap */
        if (object->state != OBJECT_NEAR_PLAYER || player->top_left.y_pos > object->bottom_left.y_pos
			|| player->bottom_left.y_pos < object->top_left.y_pos)  continue;
		
		
		if(object->type == TRIANGLE) {
			
			 if(point_inside_triangle( &(player->bottom_left), object)   ||
               point_inside_triangle( & (player->bottom_right), object) ||
               point_inside_triangle( &(player->top_left), object)   ||
               point_inside_triangle( & (player->top_right), object)  ) {
                return TRUE;
            }
			
		} else {
			/*check against the platform, there should be vertical overlap but not with the very top edge of the platform, hence > not >=*/
			if(player->bottom_left.y_pos > object->top_left.y_pos) {
					return TRUE;
			}
			
		
	
		}
       
    }
    /* No collision was detected*/
    return FALSE;
}




/*********************************************************
 * Purpose: Checks if a point is inside a triangle.
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
 * 3. Left half check: A hypothetical Y-coordinate on the hypotenuse from the bottom left vertex is calculated. If the point's Y is below this, it's inside the left half.
 * 4. Right half check: Similarly, a Y-coordinate on the hypotenuse from the top vertex determines if the point is inside the right half.
 * 5. A point is outside triangle if it does not meet either condition
 *
 *
 *********************************************************/

bool point_inside_triangle(Vertex* point, Game_Object *triangle) {

    int y_on_hypotenuse_from_bot_left, y_on_hypotenuse_from_top;
    int point_x_pos = point->x_pos , point_y_pos = point->y_pos  ; /* The slope is int't really 2, this is added into to offset the issue of premature collision*/

    if(point_y_pos < triangle->top_right.y_pos || point_y_pos > triangle->bottom_left.y_pos) {
            return FALSE; /*Point is not close to the triangle*/
    }

    /* Check if the point is within the left half of the triangle */
    if(point_x_pos >= triangle->bottom_left.x_pos && point_x_pos <= triangle->top_right.x_pos) {
        y_on_hypotenuse_from_bot_left = -((point_x_pos - triangle->bottom_left.x_pos) << 2) + triangle->bottom_left.y_pos;
        if (y_on_hypotenuse_from_bot_left <= point_y_pos) {
            return TRUE;       /*point is inside left half of the triangle*/
        }
    }

    /* Check if the point is within the right half of the triangle */
    if(point_x_pos >= triangle->top_right.x_pos  && point_x_pos<= triangle->bottom_right.x_pos) {

        y_on_hypotenuse_from_top = ((point_x_pos - triangle->top_right.x_pos) << 2) + triangle->top_right.y_pos;
        if (y_on_hypotenuse_from_top <= point_y_pos) {
            return TRUE;      /*point is inside right half of the triangle */
        }
    }
    /*Point is outside triangle*/
    return FALSE;

}



