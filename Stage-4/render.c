#include "render.h"
#include "bitmaps.h" 

/* global variable for testing purposes */
bool ground_drawn = FALSE;

/* Master render function */
void render(const Model* model, UINT32* base) {
    int curr_num_triangles = 0;
    int curr_num_platforms = 0;

    if (ground_drawn == FALSE) {
         /* draw the ground */
        draw_32_bit_bitmap(base, 0, model->ground.y_pos, 128, 640, ground_img);
        ground_drawn = TRUE;
    }
    
    /* draw the player */
    draw_32_bit_bitmap(base, model->player[0].top_left.x_pos,
                        model->player[0].top_left.y_pos, 32, 32, player_img);

    /* draw player 2 */
    if (model->num_active_players == 2) {
        draw_32_bit_bitmap(base, model->player[1].top_left.x_pos,
                        model->player[1].top_left.y_pos, 32, 32, player_img);
    }

    /* draw all triangles */
    while (curr_num_triangles < model->num_active_triangles) {
        draw_32_bit_bitmap(base, model->triangles[curr_num_triangles].hot_spot.x_pos,
                            model->triangles[curr_num_triangles].hot_spot.y_pos,
                            32, 32, triangle_img);
        curr_num_triangles++;
    
    }
    /* draw all platforms */
    while (curr_num_platforms < model->num_active_platforms) {
        draw_32_bit_bitmap(base, model->platform[curr_num_platforms].top_left.x_pos,
                            model->platform[curr_num_platforms].top_left.y_pos,
                            32, 64, platform_img);
        curr_num_platforms++;

    }





}