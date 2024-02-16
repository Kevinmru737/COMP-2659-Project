#include "events.h"

/****************************** SYNCHRONOUS EVENTS ******************************/

/* Author: Kevin
 *
 * Purpose: This event synchronously happens every screen refresh and moves
 *          all active triangle objects right to left across the screen.
 *
 * Details:
 *   Calls the function to move the triangles in models.h
 */
void move_all_active_triangles(Model *model) {

    short i = 0;
     for (i; i < model->num_active_triangles; i++) {
        move_triangle(&model->triangles[i]);
    }

}



/*
* Author: Depanshu
*
* Purpose: Checks if the player has died by detecting unsafe collisions with
*          platforms or triangles.
*
* Details:
*   This function iterates through all active platforms and triangles within the
*   game model. It checks for unsafe collisions using the platform_collision_unsafe
*   and player_triangle_collison functions. If any such collision is detected, the
*   function returns TRUE, signaling that the player has died. Otherwise, it
*   returns FALSE, allowing the game to continue.
*
* Parameters:
*   - model: A pointer to the Model struct representing the game model, which
*            includes player information and active game objects such as
*            platforms and triangles.
*   - player_num: which player to check
*
* Returns:
*   - TRUE if the player has collided in an unsafe manner with any game object,
*     leading to death.
*   - FALSE if no such collision has occurred
*/
bool player_died(Model *model, short player_num) {
    short i = 0;

    /* Check for unsafe collision with platforms */
    for (i; i < model->num_active_platforms; i++) {
        if (platform_collision_unsafe(&model->player[player_num], &model->platform[i]) == TRUE) {
            return TRUE; 
        }
    }

    /* Check for collision with triangles */
    for (i = 0; i < model->num_active_triangles; i++) {
        if (player_triangle_collison(&model->player[player_num], &model->triangles[i]) == TRUE) {
            return TRUE; 
        }
    }

    return FALSE; /*no deadly collision*/
}




/* Author: Kevin
 *
 * Purpose: This event synchronously happens every screen refresh and moves
 *          a all active platforms object right to left across the screen.
 *
 * Details:
 *   Calls the function to move the platforms in models.h
 *
 */
void move_all_active_platforms(Model* model) {
    short i = 0;
     for (i; i < model->num_active_platforms; i++) {
        move_platform(&model->platform[i]);
    }
}






/****************************** ASYNCHRONOUS EVENTS ******************************/
/* Author: Depanshu
*
*  Purpose: Sets the player's jump property to true if the player is not falling
*/
void jump_request(Model * model, short player_num) {
    if(is_player_not_falling(model, player_num) == TRUE) {
    jump(&(model->player[0]),5);
    }
}




void pause_request() {
    /* TBD*/
}

void quit_request() {
    /* Pressing ESC will close the entire game at any point. */
}






/******************************************** CONDITIONAL EVENTS ********************************************/







/* Author :Depanshu
 * Purpose: Moves the all active players vertically if they are falling or jumping.
 *
 * Parameters:
 *   - model: A pointer to the Model struct representing the game model
 *
 */
void move_all_active_players(Model *model) {
    short i = 0;

    for (i; i < model->num_active_players; i++) {

        if (is_player_not_falling(model, i) == TRUE || model->player[i].is_jumping == TRUE) {
            move_player_vert(&model->player[i]);
            
            model->player[i].is_jumping = FALSE;
        }
    }
}






