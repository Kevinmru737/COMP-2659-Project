

/****************************** SYNCHRONOUS EVENTS ******************************/

/* Author: Kevin
 *
 * Purpose: This event synchronously happens every screen refresh and moves
 *          a triangle object right to left across the screen.
 *
 * Details:
 *   Calls the function to move the triangle in models.h
 */
void triangle_moving(Triangle* triangle) {
    move_triangle(triangle);
}


/* Author: Kevin
 *
 * Purpose: This event synchronously happens every screen refresh and moves
 *          a platform object right to left across the screen.
 *
 * Details:
 *   Calls the function to move the platform in models.h
 *
 */
void platform_moving(Platform* platform) {
    move_platform(platform);
}



void player_death() {
    /* I believe we would need to add a different menu/death/victory screen model
    and create that here */
}



void player_victory() {
    /* I believe we would need to add a different menu/death/victory screen model
    and create that here */
}


/* Author: Kevin
 *
 * Purpose: This event occurs after a player has performed a jump and is currently
 *          still jumping.
 *
 * Details:
 *   Calls the function to move the player (simulates gravity) in models.h, only y-position
 *   of the player is affected.
 *
 */
void player_jumping(Player* player) {
    if (player->is_jumping == TRUE) {
        move_player(player);
    } 
}




/* Author: Depanshu
* Purpose: Performs a preliminary collision check between a player and a triangle.
*
* This function quickly determines if a detailed collision check is necessary
*  by comparing the  positions of the player and triangle, allowing for early
*  exit in clear no-collision cases. If a potential collision is detected,
*  it calls `player_triangle_collison_helper` to check
*/
bool player_triangle_collison( Player* player , Triangle * triangle){
    
    if( triangle->bot_left.x_pos > player->bot_right.x_pos||
        triangle->bot_right.x_pos > player->bot_left.x_pos||
        triangle->top.y_pos < player->bot_right.y_pos||
        triangle->bot_right.y_pos > player->top_left.y_pos||) {

            return false;
        }

    return player_triangle_collison_helper(player, triangle)

}



/****************************** ASYNCHRONOUS EVENTS ******************************/

void jump_request(Player* player) {
    jump(player);
}

void pause_request() {
    /* TBD*/
}

void quit_request() {
    /* Pressing ESC will close the entire game at any point. */
}

void increment_attempt() {

}


/****************************** CONDITIONAL EVENTS ******************************/
/* Author: Kevin
 *
 * Purpose: This event checks for player/ground collision.
 *
 * Details:
 *   Returns TRUE if a collision was detected and FALSE if there is no collision.
 *
 * Restrictions: 
 *   y position comparisons are based on the bit positions as they would appear
 *   on screen.
 */
bool ground_collision(Player* player, Ground* ground) {
    if (player->bot_left.y_pos >= ground->y_pos) {
        return TRUE;
    }
    return FALSE;
}



/* Author: Kevin
 *
 * Purpose: This event checks for unsafe player/platform collision.
 *
 * Details:
 *   Returns TRUE if an unsafe collision was detected and FALSE if there
 *   is no collision.
 *   -TRUE means the player has had an UNSAFE collision and death should occur
 *   -FALSE means the player has not yet had an unsafe collision with a platform.
 * Restrictions: 
 *   x and y position comparisons are based on the bit positions as they would
 *   appear on screen.
 */
bool platform_collision_unsafe(Player* player, Platform* platform) {
    if (player->bot_right.x_pos >= platform->bot_left.x_pos && 
        (player->bot_right.y_pos >= platform->top_left.y_pos) ||
        (player->top_right.y_pos <= platform->bot_left.y_pos)) {
            return TRUE;
    }
    return FALSE;
}

/* Author: Kevin
 *
 * Purpose: This event checks for safe player/platform collision.
 *
 * Details:
 *   Returns TRUE if a safe collision was detected and FALSE if there
 *   is no collision.
 *   -TRUE means the player has had a SAFE collision and that they should
 *   be subject to a constant y position.
 *   -FALSE means the player has not yet collided with a safe platform.
 * Restrictions: 
 *   x and y position comparisons are based on the bit positions as they would
 *   appear on screen.
 */
bool platform_collision_safe(Player* player, Platform* platform) {
    if (player->bot_right.x_pos >= platform->bot_left.x_pos && 
        (player->bot_right.y_pos <= platform->top_left.y_pos) ||
        (player->top_right.y_pos >= platform->bot_left.y_pos)) {
            return TRUE;
    }
    return FALSE;
}



/* Author: Kevin
 *
 * Purpose: This event checks for the player/victory_wall collision.
 *
 * Details:
 *   Returns TRUE if a collision was detected and FALSE if there is no collision.
 *   -TRUE means the player has won and the victory screen should be shown.
 *   -FALSE means the player has not yet collided with the victory_wall but does
 *   not cause death.
 *
 * Restrictions: 
 *   x and y position comparisons are based on the bit positions as they would
 *   appear on screen.
 */
bool victory_collision(Player* player, Victory_Wall* victory_wall) {
    if (player->bot_right.x_pos >= victory_wall->top_left.x_pos) {
            return TRUE;
        }
    return FALSE;
}

void reset_attempt(Attempt* prev_attempt_number) {
    prev_attempt_number->attempt_number = 1;
}

/* Author: Depabshu
*
 * Purpose: This function checks for collision between a player and a triangle.
 *
 * Details:
 *   - Returns TRUE if a collision was detected and FALSE if there is no collision.
 *   - The triangle is represented by three lines, and collision can occur along its two diagonal lines.
 *   - The slopes of the diagonal lines have been calculated to be 2 and -2 from the bitmap data.
 *   - There are three possible collision scenarios:
 *       1: The bottom-right edge of the player collides with the diagonal line from the bottom-left vertex of the triangle.
 *       2: The entire bottom edge (line) of the player collides with the top vertex of the triangle.
 *       3: The bottom-left edge of the player collides with the diagonal line from the top vertex of the triangle.
 */
player_triangle_collison_helper( Player* player , Triangle * triangle) {
    int y;

    /*Check if player is along the right diagnol line towards vertex */
    y = 2 * (Player->bot_right.x_pos - triangle->bot_left.x_pos) + triangle->bot_left.y_pos;

    if (y == Player->bot_left.y_pos) {
        return true;
    }

    /*Check if player is along the downward diagnol line from the vertex*/
    y = -2 * (Player->bot_left.x_pos - triangle->top.x_pos) + triangle->top.y_pos;

    if (y == Player->bot_left.y_pos) {
        return true;
    }

    /*Check if player is bottom edge of the player collides with  the top vertex of the triangle*/
    if( player->bot_left.y_pos == triangle->top.y_pos &&
        player->bot_right.x_pos >= triangle->top.x_pos &&
        player->bot_left.x_pos <= triangle->top.x_pos) {
            return true;
        }

    /* No collison occured */
    return false;

}

