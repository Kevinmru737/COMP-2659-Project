/*Author: Kevin and Depanshu*/

#include "events.h"

/****************************** SYNCHRONOUS EVENTS ******************************/

/*******************************************************************************
 * * Purpose: Iterates over all active game objects within the model to update
 *          their states based on current conditions.
 *
 * Input: A pointer to a Model struct containing the game's current state,
 *        including all game objects. 
 *
 * Output: Updates each game object based on its type (player, platform, triangle)
 *         and current state. 
 *
 * Details: This function loops through each active game object, applying
 *          updates depending on whether the object is a player or another type of
 *          game object (e.g., platform or triangle). For players, it checks their
 *          state (moving up, moving down, on a platform) and applies appropriate
 *          state transitions and velocity changes. 
*******************************************************************************/
void update_game_objects(Model * model) {
    short i = 0;

    for (i; i < model->num_active_objects; i++) {
        if(model->game_objects[i].type == PLAYER) {
            switch(model->game_objects[i].state) {

                case (PLAYER_STATE_MOVING_UP):
                    update_player_state_moving_up(&(model->game_objects[i]));
                    break;
                case (PLAYER_STATE_MOVING_DOWN):
                    update_player_state_moving_down(model);
                    break;
                case (PLAYER_STATE_ON_PLATFORM):
                    update_player_state_on_platform(model);
                    break;
                default:
                    break;
            
            }
				
        } else {
            update_platform_or_triangle(&(model->game_objects[i]));
        }
    }
	
}


/*******************************************************************************
 * Purpose: Updates the player's position and velocity when they are moving upwards.
 *
 * Input: A pointer to a Game_Object struct (`player`) representing the player
 *        whose state is being updated.
 *
 * Output: Modifies the player's vertical position based on their current velocity
 *         and decreases their velocity to simulate gravity. Transitions the
 *         player's state to moving down once their velocity becomes negative.
 *
 * Details: This function modifies the player's y-position of all four
 *          corners and decreases their vertical velocity to simulate the effect
 *          of gravity. If the adjusted velocity becomes less than 0, indicating
 *          the peak of the jump, it changes the player's state to indicate they
 *          are now moving downwards.
*******************************************************************************/

 void update_player_state_moving_up(Game_Object * player) {
    player->top_right.y_pos -= player->object_velocity;
    player->top_left.y_pos = player->top_right.y_pos;
    player->bottom_right.y_pos -= player->object_velocity;
    player->bottom_left.y_pos = player->bottom_right.y_pos;
    player->object_velocity -= DEFAULT_OBJECT_VELOCITY;

    if (player->object_velocity < 0) {
        player->state = PLAYER_STATE_MOVING_DOWN;
    }

}
/*******************************************************************************

 * Purpose: Updates the player's position and state when they are moving downwards,
 *          either after a jump or falling off a platform.
 *
 * Input: A pointer to the Model struct (`model`) representing the game's current state
 *
 * Output: Modifies the player's vertical position based on their current velocity.
 *         If the player collides with the ground or a platform, their position and
 *         state are updated accordingly.
 *
 * Details: Checks if the player is colliding with a platform during their descent.
 *          If not, and if they reach the ground, the function updates their position
 *          to stand on the ground and sets their state to indicate they are on the
 *          ground. If still in the air, it continues to adjust their position based
 *          on velocity and applies deceleration until a collision occurs.
 *
 * * Assumptions:
 *        - The first object in the game_objects array is the player.
 *
*******************************************************************************/
void update_player_state_moving_down(Model * model) {
    Game_Object *player = &model->game_objects[PLAYER_INDEX];
    int new_y_pos_top = player->top_right.y_pos - player->object_velocity;
    int new_y_pos_bottom = player->bottom_right.y_pos - player->object_velocity;

    if(check_player_safe_collision_with_platform(model) == FALSE) {
        if (new_y_pos_bottom >= GROUND_POS) {

            player->top_right.y_pos = GROUND_POS - DEFAULT_OBJECT_HEIGHT;
            player->top_left.y_pos = GROUND_POS - DEFAULT_OBJECT_HEIGHT;
            player->bottom_left.y_pos = GROUND_POS;
            player->bottom_right.y_pos = GROUND_POS;
            player->object_velocity = 0;
            player->state = PLAYER_STATE_ON_GROUND;

        } else {
            player->top_right.y_pos = new_y_pos_top;
            player->top_left.y_pos = new_y_pos_top;
            player->bottom_left.y_pos = new_y_pos_bottom;
            player->bottom_right.y_pos = new_y_pos_bottom;

            if (player->object_velocity > PLAYER_TERMINAL_VELOCITY) {
                player->object_velocity -= DEFAULT_OBJECT_VELOCITY;
            }
        }

    }
	
	
	
	
	


}
/*******************************************************************************
* Purpose: Ensures the player remains correctly positioned on a platform, adjusting
 *          their state if they move off the platform.
 *
 * Input: A pointer to the Model struct (`model`) representing the game's current
 *        state, and a short (`player_num`) indicating the player's index within
 *        the game model's object array.
 * Output: Checks and maintains the player's position on the platform. If the player
 *         is no longer positioned on any platform, their state is updated to moving
 *         down.
 *
 * Details: Loops through all game objects to check if the player is still on a platform.
 *          If the player's bottom position aligns with the top of any platform, it
 *          maintains their current state. Otherwise, it updates the player's state
 *          to indicate they are falling.
 * Assumptions:
 *        - The first object in the game_objects array is the player.
 *
 *******************************************************************************/

void update_player_state_on_platform(Model * model) {
    Game_Object *player = &model->game_objects[PLAYER_INDEX];
    bool player_moving_down = TRUE;
    short i = PLAYER_INDEX + 1;
    for (i; i < model->num_active_objects; i++) {
        if (model->game_objects[i].type != TRIANGLE &&
            model->game_objects[i].state == OBJECT_NEAR_PLAYER) {

            if(player->bottom_left.y_pos == model->game_objects[i].top_left.y_pos)
                player_moving_down = FALSE;
            }

        }
    if(player_moving_down == TRUE) {
        player->state = PLAYER_STATE_MOVING_DOWN;
    }

}


/*******************************************************************************
 * Purpose: Updates the position of platform or triangle objects within the game.
 *
 * Input: Pointer to a Game_Object struct representing a platform or triangle.
 * Output: Object's position updated based on its velocity.
 *
 * Details: The function updates the x position of all vertices of the object
 *          based on its velocity. If the object is not already marked as left off
 *          from the player and crosses the left edge, its state is set to
 *          OBJECT_LEFT_OFF_PLAYER. Objects near the player are updated to
 *          OBJECT_NEAR_PLAYER based on their proximity to the player.
*******************************************************************************/
void update_platform_or_triangle(Game_Object * object) {
    object->top_right.x_pos -= object->object_velocity;
    object->top_left.x_pos -= object->object_velocity;
    object->bottom_left.x_pos -= object->object_velocity;
    object->bottom_right.x_pos -= object->object_velocity;

    if(object->state != OBJECT_LEFT_OFF_PLAYER) {
        if( object->bottom_right.x_pos < PLAYER_LEFT_EDGE_X_POS) {
            object->state = OBJECT_LEFT_OFF_PLAYER;
        } else if(object->bottom_left.x_pos <= PLAYER_RIGHT_EDGE_X_POS){
            object->state = OBJECT_NEAR_PLAYER;
        }
    }
}


/*******************************************************************************
 * Purpose: Checks for safe collisions between the player and
 *          platforms to determine if the player lands on a platform during
 *          their descent.
 *
 * Input: A pointer to the Model struct (`model`) representing the game's current
 *        state
 *
 * Output: Returns TRUE if the player safely collides with the top of a platform,
 *         otherwise FALSE. Upon collision, updates the player's position to
 *         stand on the platform and adjusts their velocity and state to
 *         reflect this new position.
 *
 * Details: This function iterates through the game objects to identify platforms
 *          near the player. It checks if the descending player's bottom position
 *          intersects with the top of any platform. If such a collision is detected,
 *          the player's vertical position is adjusted to align with the platform's
 *          top surface, their vertical velocity is reset, and their state is updated
 *          to indicate they are standing on a platform, stopping their descent
 * Assumptions:
 *        - The first object in the game_objects array is the player.
 *
 *******************************************************************************/
bool check_player_safe_collision_with_platform(Model * model) {
    int platform_y_pos_top;
    Game_Object *player = &model->game_objects[PLAYER_INDEX];
    int new_y_pos_bottom = player->bottom_right.y_pos - player->object_velocity;
    short i = PLAYER_INDEX + 1;
	bool player_safe_on_platform = FALSE;
    
    for (i; i < model->num_active_objects; i++) {
    
        if(model->game_objects[i].type == TRIANGLE ||
          model->game_objects[i].state != OBJECT_NEAR_PLAYER) continue;

          platform_y_pos_top = model->game_objects[i].top_right.y_pos;

          if (player->bottom_left.y_pos <= platform_y_pos_top &&
              new_y_pos_bottom >= platform_y_pos_top) {

            player->top_right.y_pos = platform_y_pos_top - DEFAULT_OBJECT_HEIGHT;
            player->top_left.y_pos = platform_y_pos_top - DEFAULT_OBJECT_HEIGHT;
            player->bottom_left.y_pos = platform_y_pos_top;
            player->bottom_right.y_pos = platform_y_pos_top;
            player->object_velocity = 0;
            player->state = PLAYER_STATE_ON_PLATFORM;

               player_safe_on_platform = TRUE;
               break; /*already safe on a platform, so no need to check further*/
            }
    }
   return player_safe_on_platform;
}


/****************************** ASYNCHRONOUS EVENTS ******************************/

/*********************************************************
 * Purpose: Triggers a jump for a player if they are safely on the ground or
*            a platform.
 *
 * Input: Pointer to a Model struct representing the game model.
 *
 * Output: Updates the vertical velocity of the player to an initial jump
 *         velocity if the player is safely on a surface or ground. Does nothing
 *         if the player is not in a safe position to jump.
 *
 * Details: Checks if the player's current state is either on the ground
 *          or on a platform. If true, the player's vertical velocity is
 *          set to an initial jump velocity, and their state is
 *          changed to PLAYER_STATE_MOVING_UP, initiating the jump.
 *
 *  Assumptions:
 *        - The first object in the game_objects array is the player.
 *
 *********************************************************/

void jump_request(Model * model) {

    if (model->game_objects[PLAYER_INDEX].state == PLAYER_STATE_ON_PLATFORM ||
        model->game_objects[PLAYER_INDEX].state == PLAYER_STATE_ON_GROUND) {

        model->game_objects[PLAYER_INDEX].object_velocity = PLAYER_INITIAL_JUMP_VELOCITY;
        model->game_objects[PLAYER_INDEX].state = PLAYER_STATE_MOVING_UP;
    }
}


/******************************************** CONDITIONAL EVENTS ********************************************/
