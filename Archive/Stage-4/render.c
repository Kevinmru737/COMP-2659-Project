#include "render.h"


/* global variable for testing purposes */
bool ground_drawn = FALSE;

/*  Master render function */
void render(const Model* model, UINT32* base) {
    if (ground_drawn == FALSE) {
         /* draw the ground */
        draw_32_bit_bitmap(base, 0, model->ground.y_pos, 128, 640, ground_img);
        ground_drawn == TRUE;
       
    }
    
    render_all_active_players(model, base);
    render_all_active_platforms(model, base);
    render_all_active_triangles(model, base);

}


/* Renders all active platforms
*/
void render_all_active_platforms (Model * model, UINT32 *base) {
    short curr_num_platforms = 0;
    
    while (curr_num_platforms < model->num_active_platforms) {
        draw_32_bit_bitmap(base, model->platform[curr_num_platforms].top_left.x_pos,
                            model->platform[curr_num_platforms].top_left.y_pos,
                            32, 64, platform_img);
        curr_num_platforms++;

    }


}

/* Renders all active triangles
*/
void render_all_active_triangles (Model * model,  UINT32 *base) {
    short curr_num_triangles = 0;

    while (curr_num_triangles < model->num_active_triangles) {
        draw_32_bit_bitmap(base, model->triangles[curr_num_triangles].hot_spot.x_pos,
                            model->triangles[curr_num_triangles].hot_spot.y_pos,
                            32, 32, triangle_img);
        
        curr_num_triangles++;
    }


}

/* Renders all active players
*/
void render_all_active_players(Model * model,  UINT32 *base) {
    short curr_num_player = 0;

    while (curr_num_player < model->num_active_players) {
        draw_32_bit_bitmap(base, model->player[curr_num_player].top_left.x_pos,
                            model->player[curr_num_player].top_left.y_pos, 32, 32, player_img);
        curr_num_player++;
    }


}
