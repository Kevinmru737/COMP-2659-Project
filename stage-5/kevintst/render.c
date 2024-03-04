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
 * Input: Const pointer to the game model, representing the current state of the
 *        game including all active objects. Pointer to the screen buffer base,
 *        where the game visuals will be rendered.
 *
 * Output: Updates the screen buffer with the current game state. The global variable
 *         'ground_drawn' controls ground rendering, ensuring it's only cleared
 *         and redrawn when necessary. For each game object, depending on its type,
 *         a specific bitmap is drawn at its current position.
*********************************************************/
void render(const Model* model, UINT32* base) {
    short i = model->num_active_objects - 1;

    if (ground_drawn < 2) {
        clear_screen(base);
        draw_32_bit_bitmap(base, 0, model->ground.y_pos, 128, 640, ground_img);
        ground_drawn++;
    } else {
        clear_except_ground(base);
    }

    for (i; i >= 0; i--) {

        if (model->game_objects[i].top_left.x_pos >= 0 && model->game_objects[i].top_left.x_pos < SCREEN_WIDTH) {
            if (model->game_objects[i].type == PLATFORM_SHORT) {
                draw_32_bit_bitmap(base, model->game_objects[i].top_left.x_pos,
                                   model->game_objects[i].top_left.y_pos,
                                   16, 32, platform_32_16);
            } 
            else if (model->game_objects[i].type == START_MESSAGE) {
                    draw_32_bit_bitmap(base, model->game_objects[i].top_left.x_pos,
                                   model->game_objects[i].top_left.y_pos,
                                   64, 384,
                                   start_message);
            } else {
                draw_32_bit_bitmap(base, model->game_objects[i].top_left.x_pos,
                                   model->game_objects[i].top_left.y_pos,
                                   32, 32,
                                   game_object_images[model->game_objects[i].type]);
            }

        }


    }
}
