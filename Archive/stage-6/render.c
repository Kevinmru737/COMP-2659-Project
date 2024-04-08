#include "render.h"
short ground_drawn = 0;

/*  Master render function */

/*********************************************************
* Purpose:Master Render Function
*
 * Details: Renders the game model by drawing the ground (if not already drawn),
 *          active players, platforms, and triangles. The ground is drawn based
 *          on the 'ground_drawn' global variable, ensuring it's only drawn twice(on two buffers).
 *
 * Input: 
 *        - Const pointer to the game model, representing the current state of the game.
 *        - Pointer to the screen buffer base, where the game visuals will be rendered.
 *
 * Output: Updates the screen buffer with the current game state. The global variable
 *         'ground_drawn' controls ground rendering. For each game object, 
 *		depending on its type, a specific bitmap is drawn at its current position.
*********************************************************/
void render(const Model* model, UINT32* base) {
    short object_index = model->num_active_objects - 1;

    if (ground_drawn < 2) {
        clear_screen(base);
        draw_32_bit_bitmap(base, 0, model->ground.y_pos, 128, 640, ground_img);
        ground_drawn++;
    } else {
        clear_except_ground(base);
    }
	
     for (object_index; object_index >= 0; object_index--) {
        if (model->game_objects[object_index].top_left.x_pos >= 0 && model->game_objects[object_index].top_left.x_pos <= RIGHT_EDGE_DRAW) {
            render_object(base, &model->game_objects[object_index]);
        }
    }
	
}


/*********************************************************
 * Function: draw_object
 *
 * Purpose: Draws a game object on the screen
 *
 * Details: Depending on the type of the game object, a specific bitmap is drawn
 *          at the object's current position.
 *
 * Input: 
 *        - Pointer to the screen buffer base, where the game visuals will be rendered.
 *        - Pointer to the game object to be drawn.
 *
 * Output: Updates the screen buffer with the drawn game object.
*********************************************************/
void render_object(UINT32* base, Game_Object* game_object) {
    switch(game_object->type) {
        case PLATFORM_SHORT:
            draw_platform_triangle(base, game_object->top_left.x_pos, game_object->top_left.y_pos, platform_32_16, TRUE);
            break;
        case PLAYER:
            draw_player(base, game_object->top_left.y_pos, game_object_images[game_object->type]);
            break;
        default:
            draw_platform_triangle(base, game_object->top_left.x_pos, game_object->top_left.y_pos, game_object_images[game_object->type], FALSE);
            break;
	}
}
