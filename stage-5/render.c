#include "render.h"


/*  Master render function */
void render(const Model* model, UINT32* base, bool *was_ground_drawn) {
	
    if (*was_ground_drawn == FALSE) {
		
		clear_screen(base);
		draw_32_bit_bitmap(base, 0, model->ground.y_pos, 128, 640, ground_img);
		render_all_active_players(model, base);
		render_all_active_platforms(model, base);
		render_all_active_triangles(model, base);
		*was_ground_drawn = TRUE;
		
		return;
    }
	
	
	clear_except_ground(base);
	
    render_all_active_platforms(model, base);
    render_all_active_triangles(model, base);
	render_all_active_players(model, base);

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
