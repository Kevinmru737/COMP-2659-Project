#include "models.h"
#include "stdio.h"
#include <stdlib.h>
#include <osbind.h>

 /* Author: Depanshu and Kevin

/***************************************************
 * Purpose: Updates the vertical position of the player.
 * 
 * Input: Pointer to Player struct
 *
 * Output: Updated y position of the player based on the vertical velocity.
 *
 *
 * Details: Adjusts the player's y position upwards or downwards by altering the top_left,
 * top_right, bot_left, and bot_right vertices' y positions. The direction is determined by the sign of
 * the vertical velocity (positive for up, negative for down).
 *
 *******************************************************/
void update_player_pos(Player * player) {

    short player_move_direction = player->vert_vel > 0 ? -1: 1;

    (player->top_left.y_pos) += player_move_direction;
    (player->top_right.y_pos) += player_move_direction;
    (player->bot_left.y_pos) += player_move_direction;
    (player->bot_right.y_pos) += player_move_direction;

}


/*********************************************************
 * Purpose: Moves a triangle leftward on the screen by one unit.
 *
 * Input: Pointer to a Triangle struct 
 * Output: Updated x positions of all triangle vertices moved left by one unit.
 *
 * Details: If the triangle reaches the left edge of the screen, it is reinitialized
 * to the right, maintaining its y position and horizontal velocity.
 *
  *******************************************************/

void update_triangle_pos(Triangle* triangle) {
	(triangle->bot_left.x_pos)--;
	(triangle->top.x_pos)--; 
	(triangle->bot_right.x_pos)--; 
	(triangle->hot_spot.x_pos)--;
	
	/*Wrap around to right edge of the screen if triangle reaches left screen edge*/
	if(triangle->bot_left.x_pos == 0) {
		initialize_triangle(608, triangle->top.y_pos, triangle->hor_vel, triangle);

	}

}

/*********************************************************
 *
 * Purpose: Moves a platform leftward on the screen by one unit.
 * 
 * Input: Pointer to  a Platform struct
 * Output: Updated x positions of all platform vertices moved left by one unit.
 *
 * Details: If the platform reaches the left edge of the screen, it is wrapped back
 * to the right edge.
 *
 *********************************************************/


/* Moves the platform in the horizontal left direction by a single unit
*/
void update_platform_pos(Platform* platform) {
	(platform->top_left.x_pos)--;
	(platform->top_right.x_pos)--;
	(platform->bot_left.x_pos)--;
	(platform->bot_right.x_pos)--;
	
	/* wraps around to right edge of the screen if platform reaches left screen edge*/
	if(platform->bot_left.x_pos == 0) {
		wrap_platfrom_back(platform);
	}


}

/*********************************************************
 * Purpose: Wraps the platform back to the right edge of the screen when it hits the left edge.
 * 
 * Input: Pointer to  a Platform struct
 * Output: Platform's position reset to the right edge with the same dimensions.
 *
 * Details: Calculates the new position based on the platform's width and height to
 * ensure it appears at the right edge.
 *
 *********************************************************/
 

void wrap_platfrom_back( Platform* platform) {
	
	int width = platform->top_right.x_pos - platform->top_left.x_pos + 1;
    int height = platform->bot_right.y_pos - platform->top_right.y_pos + 1;
    initialize_platform(640 - width, platform->top_right.y_pos, width, height, platform->hor_vel, platform);

}


/*********************************************************
 * Purpose:  Initializes a triangle with the given position and velocity.
 * 
 * Input:  x, y coordinates for initial position; horizontal velocity; pointer to Triangle struct.
 * Output: Triangle struct initialized with specified position, velocity, and dimensions.
 *
 * Restriction:
 *		  - No bounds checking is done so, user has to give valid parameters
 *
 *********************************************************/
void initialize_triangle(int x, int y, short hor_vel, Triangle* new_triangle) {
	new_triangle->hot_spot.x_pos = x;
	new_triangle->hot_spot.y_pos = y;

	new_triangle->bot_left.x_pos = x;
	new_triangle->bot_left.y_pos = y + 31;

	new_triangle->bot_right.x_pos = x + 31;
	new_triangle->bot_right.y_pos = y + 31;

	new_triangle->top.x_pos = x + 15;
	new_triangle->top.y_pos = y;

	new_triangle->hor_vel = hor_vel;
}


/*********************************************************
 * Purpose:  Initializes a platform with the given position and velocity.
 * 
 * Input:  x, y coordinates for initial position; horizontal velocity; pointer to Platform struct.
 * Output: Platform struct initialized with specified position, velocity, and dimensions.
 *
 * Restriction:
 *		  - No bounds checking is done so, user has to give valid parameters
 *
 *********************************************************/
void initialize_platform(int x, int y, int width, int height, int hor_vel, Platform* new_platform) {
	new_platform->top_left.x_pos = x;
	new_platform->top_left.y_pos = y;

	new_platform->top_right.x_pos = x + (width - 1);
	new_platform->top_right.y_pos = y;

	new_platform->bot_left.x_pos = x;
	new_platform->bot_left.y_pos = y + (height - 1);

	new_platform->bot_right.x_pos = x + (width - 1);
	new_platform->bot_right.y_pos = y + (height - 1);

	new_platform->hor_vel = hor_vel;
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
void initialize_ground(int y, Ground* ptr_ground) {
	ptr_ground->y_pos = y;
}


/*********************************************************
 * Purpose:  Initializes a player with specified position
 * 
 * Input: x, y coordinates for initial position; pointer to Player struct.
 * Output: Player struct initialized with specified position and zero vertical velocity.
 *
 * Details: The player's initial position is determined by the x and y parameters, which define the top-left corner
 *   	   of the player's square. The player is assumed to have a square box with a size of 32x32 pixels
 *   	   (hence the addition of 31 pixels to x and y for bottom and right sides).
 * Restriction:
 *		  - No bounds checking is done so, user has to give valid parameters
 *
 *********************************************************/
void initialize_player(int x, int y, Player* player) {
	player->top_left.x_pos = x;
	player->top_left.y_pos = y;
	player->top_right.x_pos = x + 31;
	player->top_right.y_pos = y;
	player->bot_left.x_pos = x;
	player->bot_left.y_pos = y + 31;
	player->bot_right.x_pos = x + 31;
	player->bot_right.y_pos = y + 31;

	player->vert_vel = 0;
	player->fatal_collision = FALSE;

}

/*********************************************************
 * Purpose:  Checks for collision between the player and a triangle.
 * 
 * Input: Pointers to Player and Triangle struct being checked for collision
 * Output: TRUE if collision detected, FALSE otherwise
 *
 * Details: Performs a coarse check followed by a detailed check using a helper function
 *
 *
 *********************************************************/
bool player_triangle_collision( Player* player , Triangle * triangle){
    
    if( triangle->bot_left.x_pos > player->bot_right.x_pos ||     /*triangle is way off right of the player */ 
        player->bot_left.x_pos > triangle->bot_right.x_pos ||    /*triangle is way off left of the player */ 
        player->top_right.y_pos > triangle->bot_left.y_pos ||    /*triangle is above the player */ 
        triangle->top.y_pos > player->bot_left.y_pos   )         /*triangle is below the player */ 
         {

            return FALSE;
        }

	/*detailed check necessary*/
    return player_triangle_collision_helper(player, triangle);

}


/*********************************************************
 * Purpose:  Helper function to check detailed collision between player and triangle.
 * 
 * Input: Pointers to Player and Triangle struct.
 * Output: TRUE if collision detected, FALSE otherwise.
 *		   PLayer's fatal_collision flag is set to TRUE if an unsafe collision is detected
 *
 * Details: Checks if any player vertices are within the triangle's area or if the player's
 * 			bottom edge collides with the triangle's top vertex.
 *
 *********************************************************/
bool player_triangle_collision_helper( Player* player , Triangle * triangle) {
	
	/*Checking if any of the player's vertex are inside the triangle*/
	if(point_inside_triangle( &(player->bot_left), triangle)   ||
	   point_inside_triangle( & (player->bot_right), triangle) || 
	   point_inside_triangle( &(player->top_left), triangle)   ||
	   point_inside_triangle( & (player->top_right), triangle)  ) {
		   player->fatal_collision = TRUE;
            return TRUE;
	   }


	/*Checking if player's bottom edge is in contact with the triangle's top vertex*/
    if( player->bot_left.y_pos == triangle->top.y_pos &&
        player->bot_right.x_pos >= triangle->top.x_pos &&
        player->bot_left.x_pos <= triangle->top.x_pos) {
			player->fatal_collision = TRUE;
            return TRUE;
        }

    /* No collision occurred */
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
 
bool point_inside_triangle(Vertex* point, Triangle *triangle) {
	
	int y_on_hypotenuse_from_bot_left, y_on_hypotenuse_from_top;
	
	if(point->y_pos < triangle->top.y_pos || point->y_pos > triangle->bot_left.y_pos) {
			return FALSE; /*Point is above or below the triangle*/
	}
	
	/* Check if the point is within the left half of the triangle */
	if(point->x_pos >= triangle->bot_left.x_pos && point->x_pos <= triangle->bot_left.x_pos + 15) {
		
		y_on_hypotenuse_from_bot_left = -2 * (point->x_pos - triangle->bot_left.x_pos) + triangle->bot_left.y_pos;
		if (y_on_hypotenuse_from_bot_left <= point->y_pos) {
			return TRUE;       /*point is inside left half of the triangle*/
		}
	}

	/* Check if the point is within the right half of the triangle */
	if(point->x_pos >= triangle->bot_left.x_pos + 15 && point->x_pos <= triangle->bot_right.x_pos) {
		
		y_on_hypotenuse_from_top = 2 * (point->x_pos - triangle->top.x_pos) + triangle->top.y_pos;
		if (y_on_hypotenuse_from_top <= point->y_pos) {
			return TRUE;      /*point is inside right half of the triangle*/
		}
	}
	
	/*Point is outside triangle*/
	return FALSE; 
	
}

/*********************************************************
 * Purpose: Checks for collision between the player and the ground.
 * 
 * Input: Pointers to Player and Ground structs.
 * Output: TRUE if collision detected, FALSE otherwise.
 *
 * Details: Compares the y position of the player's bottom edge with the ground's y position
 * to determine collision.
 *
 *********************************************************/
bool ground_collision(Player* player, Ground* ground) {
    if (player->bot_left.y_pos >=  ground->y_pos) {
        return TRUE;
    }
    return FALSE;
}


 
 
 /*********************************************************
 * Purpose: Checks for unsafe collision between the player and a platform.
 *
 * Input: Pointers to Player and Platform structs
 * Output: Returns TRUE if an unsafe collision is detected, FALSE otherwise. 
 *		   PLayer's fatal_collision flag is set to TRUE if an unsafe collision is detected
 *
 * Details: The function checks two specific collision scenarios:
 * 			- Vertical collision: When the player's top edge intersects with the platform's bottom edge.
 * 			- Horizontal collision: When the player's right edge intersects with the platform's left edge.
 *
 *********************************************************/
bool platform_collision_unsafe(Player* player, Platform* platform) {

    /* Check for collision between the player's top edge and the platform's bottom edge */
    if(player->top_left.y_pos == platform->bot_right.y_pos &&
       player->top_right.x_pos >= platform->bot_left.x_pos &&
       platform->bot_right.x_pos >= player->top_left.x_pos) {
			player->fatal_collision = TRUE;
            return TRUE;
        }

    /*Check for collision between the player's right edge and the platform's left edge*/
    if(player->top_right.x_pos ==  platform->top_left.x_pos &&
       platform->top_left.y_pos >= player->top_right.y_pos  &&
       player->bot_right.y_pos >= platform->top_left.y_pos) {
			player->fatal_collision = TRUE;
            return TRUE;
        }


    /* No collision was detected*/
    return FALSE;
}





/*********************************************************
 * Purpose: Checks for safe collision between the player and a platform.
 * 
 * Input: Pointers to Player and Platform structs.
 * Output: TRUE if safe collision detected, FALSE otherwise.
 *
 *
 *********************************************************/
bool platform_collision_safe(Player* player, Platform* platform) {

    /*Checking if player's bottom edge is on top of the platform's top edge*/
    if(player->bot_right.y_pos == platform->top_left.y_pos &&
        player->bot_right.x_pos > platform->top_left.x_pos &&
        player->bot_left.x_pos <= platform->top_right.x_pos) {
            return TRUE;
    }

    return FALSE;
}





/*********************************************************
 * Purpose: Checks for collision between the player and the victory wall.
 * 
 * Input: Pointers to Player and Victory_Wall structs.
 * Output: TRUE if collision detected, FALSE otherwise.
 *
 *********************************************************/
bool victory_collision(Player* player, Victory_Wall* victory_wall) {
    return player->bot_right.x_pos >= victory_wall->top_left.x_pos ? TRUE : FALSE;
}





/*********************************************************
 * Purpose: Determines if the player is safely on the ground or a platform.
 * 
 * Input: Pointer to Model struct containing the game state, player number(player being checked).
 * Output: TRUE if player is safely on ground or a platform, FALSE otherwise.
 *
 * Details: Checks for safe collisions with the ground or any active platforms
 *
 *********************************************************/
bool player_safe_on_ground_or_surface(Model *model, short player_num) {
    short i = 0;
    if ( ground_collision( &(model->player[player_num]), &(model->ground) ) ) {
        return TRUE;
    }

    for( i; i < model->num_active_platforms; i++) {
        if( platform_collision_safe(&model->player[player_num], &model->platform[i] ) == TRUE) {
            return TRUE;
        }
    }

    return FALSE;
}



/*********************************************************
 * Purpose: Checks for fatal collisions between a player and obstacles (any active triangle or platform).
 * 
 * Input: Pointer to Model struct containing game state, player number(player being checked).
 * Output: TRUE if fatal collision detected with any active triangle or platform, FALSE otherwise.
 *
 * Details: Uses a helper functions to assess collisions separately for each obstacle type.
 *
 *********************************************************/

bool player_fatal_collision(Model *model, short player_num) {

	return has_player_collided_with_any_triangle(model, player_num) || has_player_collided_with_any_platform(model, player_num);

}



/*********************************************************
 * Purpose: Helper function to check for fatal collisions with all active triangles
 * 
 * Input: Pointer to Model struct containing game state, player number.
 * Output: TRUE if fatal collision detected with any active triangle, FALSE otherwise.
 *
 * Details: Iterates over all active triangles, and checks for a collision with the specified player.
 *         Uses player_triangle_collision function to check for collision between each active triangle and player
 *
 *********************************************************/
bool has_player_collided_with_any_triangle(Model *model, short player_num){
	
	short i = 0;

    for( i; i < model->num_active_triangles; i++) {
        if( player_triangle_collision(&model->player[player_num], &model->triangles[i] ) == TRUE) {
            return TRUE;
        }
    }
	
	return FALSE;

}

/*********************************************************
 * Purpose: Helper function to check for fatal collisions with all active platforms
 * 
 * Input: Pointer to Model struct containing game state, player number.
 * Output: TRUE if fatal collision detected with any active platform, FALSE otherwise.
 *
 * Details: Iterates over all active platforms, and checks for a collision with the specified player.
 *         Uses platform_collision_unsafe function to check for collision between each active platform and player
 *
 *********************************************************/
bool has_player_collided_with_any_platform(Model *model, short player_num){
	short i = 0;
	for( i; i < model->num_active_platforms; i++) {
        if( platform_collision_unsafe(&model->player[player_num],&model->platform[i] ) == TRUE) {
            return TRUE;
        }
    }
	return FALSE;
}