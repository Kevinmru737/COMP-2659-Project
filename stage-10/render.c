#include "render.h"
int prev_mouse_drawn_x = 320;
int prev_mouse_drawn_y = 200;

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
void render(const Model* model, UINT32* base,  short *num_times_ground_drawn) {
    short object_index = model->num_active_objects - 1;

    if (*num_times_ground_drawn < MAX_TIMES_TO_DRAW_GROUND) {
        clear_screen(base);
        draw_32_bit_bitmap(base, 0, model->ground.y_pos, 128, 640, ground_img);
        (*num_times_ground_drawn)++;
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

/*********************************************************
 * Purpose: Renders the current score on the game display based on the game state.
 *
 * Details: This function uses a bitmap image to represent the score on the screen.
 *
 * Input: base - Pointer to the base address of the buffer where the score will be rendered.
 *        game_state - Integer representing the current state of the game, which determines the score image to use.
 *
 * Output: Updates the specified buffer with the visual representation of the current score.
 *********************************************************/
void render_score(UINT32* base, int game_state){
    draw_8_bit_bitmap((UINT8 *) base,SCORE_BAR_X_POS,SCORE_BAR_Y_POS, SCORE_BAR_HEIGHT, SCORE_BAR_WIDTH,scores[game_state]);
}



/*********************************************************
 * Purpose: Renders an explosion animation at the player's location in the game.
 *
 * Details: This function overlays an explosion bitmap on the current frame being rendered to  represent an explosion.
 *
 * Input: model - Constant pointer to the game model containing state and object positions.
 *        base - Pointer to the base address of the buffer where the game frame, including the explosion, will be rendered.
 *        explosion_counter - Short integer indicating the current frame of the explosion animation to display.
 *
 * Output: Updates the specified buffer with the current game frame, including the explosion animation at the player's location.
 *********************************************************/
void render_explosion(const Model* model, UINT32* base, short explosion_counter){
	draw_8_bit_bitmap((UINT8*) base, model->game_objects[PLAYER_INDEX].top_left.x_pos,
                    model->game_objects[PLAYER_INDEX].top_left.y_pos, EXPLOSION_HEIGHT, EXPLOSION_WIDTH, 
                    explosion_images[explosion_counter]);

}



/**************************************
 * Purpose: Draws the 640 x 400 splash screen
 *
 *****************************************/
void render_splash_screen(UINT16 *base) {
    draw_16_bit_bitmap(base,0, 0,400,640, splash_screen);

}


/**************************************
 * Purpose:
 *
 *****************************************/
void render_mouse(UINT16 *base, UINT16 *base_2) {
    int currrent_mouse_x = mouse_curr_x;
    int currrent_mouse_y = mouse_curr_y;
    UINT16 *screen = splash_screen;
    UINT16 *cur = cursor;
  

    int row = 0;
    int start_bit_position = mouse_curr_x & 15; /*which bit to start drawning on*/
    int bits_in_first_long = UINT16_SIZE_BITS - start_bit_position;


    base_2 += OFFSET_TO_UINT16(prev_mouse_drawn_x,prev_mouse_drawn_y);
    screen += OFFSET_TO_UINT16(prev_mouse_drawn_x,prev_mouse_drawn_y);



	for(row;row < 16; row++) {
        *base_2++ = *screen++;
        *base_2 = *screen;
		base_2 += UINT16_PER_SCANLINE - 1;
        screen += UINT16_PER_SCANLINE - 1;
    }	

    base += OFFSET_TO_UINT16(mouse_curr_x,mouse_curr_y); 

	for(row = 0;row < 16; row++) {
         *base |= (*cur) >> start_bit_position;
         base++;
         *base |= (*cur) << bits_in_first_long;
         cur++;
		base += UINT16_PER_SCANLINE - 1;
    }	
    
    prev_mouse_drawn_x = mouse_curr_x;
    prev_mouse_drawn_y = mouse_curr_y;

}