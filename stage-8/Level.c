
#include "Level.h"

LEVEL_UPDATE_FUNCTIONS lvl_update_functions[] = {
        lvl_1,
        lvl_2,
        lvl_3,
        lvl_4,
        lvl_5,
        lvl_6,
        lvl_7,
        lvl_8,
		lvl_9,
		lvl_10
};


void update_level(Model *model, UINT8 *game_state) {
    lvl_update_functions[(*game_state)](model, game_state);
}


void lvl_1(Model *model, UINT8* game_state) {
    model->num_active_objects = 12;
    initialize_game_object(PLAYER_START_X,PLAYER_START_Y, &(model->game_objects[0]), PLAYER);
    initialize_ground( &( model->ground ) );

    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 ,OFFSET_38_UP_FROM_GROUND , &(model->game_objects[1]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[2]), TRIANGLE);
    
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 96, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 96, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_BRICK_1);

    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 128 , OFFSET_32_UP_FROM_GROUND, &(model->game_objects[5]), TRIANGLE);
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 192 ,OFFSET_48_UP_FROM_GROUND, &(model->game_objects[6]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 256 ,OFFSET_32_UP_FROM_GROUND , &(model->game_objects[7]), TRIANGLE);


    
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 288, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[8]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 320, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[9]), TRIANGLE);
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 384, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[10]), PLATFORM_BRICK_1);
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 384, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[11]), PLATFORM_BRICK_1);
    (*game_state)++;

}
void lvl_2(Model*model, UINT8* game_state) {
    
    if(model->game_objects[11].bottom_right.x_pos < 0) {
        model->num_active_objects = 5;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 , OFFSET_64_UP_FROM_GROUND , &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[3]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[4]), TRIANGLE);
        (*game_state)++;
    }

}

void lvl_3(Model *model, UINT8 *game_state) {
  if(model->game_objects[4].bottom_right.x_pos < 0) {
        model->num_active_objects = 5;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_71_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_BRICK_2);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[2]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[3]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64, OFFSET_71_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_1);
        (*game_state)++;
    }

}

void lvl_4(Model*model, UINT8* game_state) {
  if(model->game_objects[4].bottom_right.x_pos < 0) {
        model->num_active_objects = 10;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,      OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 84, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 180,OFFSET_64_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_SHORT);
		initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 270, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 42, OFFSET_32_UP_FROM_GROUND  , &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 126, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[6]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 222, OFFSET_32_UP_FROM_GROUND  , &(model->game_objects[7]), TRIANGLE);
		initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 286, OFFSET_32_UP_FROM_GROUND  , &(model->game_objects[8]), TRIANGLE);
		initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 318, OFFSET_32_UP_FROM_GROUND  , &(model->game_objects[9]), TRIANGLE);
        (*game_state)++;
    }

}


void lvl_5(Model *model, UINT8 *game_state) {
  if (model->game_objects[9].bottom_right.x_pos < 0) {
        model->num_active_objects = 6;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,OFFSET_48_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[2]), PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[3]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[4]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 96, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[5]), PLATFORM_1);
        (*game_state)++;
    }

}
void lvl_6(Model*model, UINT8 *game_state) {
    if (model->game_objects[6].bottom_right.x_pos < 0) {
        model->num_active_objects = 7;

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32,  OFFSET_64_UP_FROM_GROUND,  &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64,  OFFSET_64_UP_FROM_GROUND,  &(model->game_objects[3]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,       OFFSET_90_UP_FROM_GROUND , &(model->game_objects[4]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32,  OFFSET_90_UP_FROM_GROUND , &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64,  OFFSET_90_UP_FROM_GROUND , &(model->game_objects[6]), TRIANGLE);    
        (*game_state)++;
    }

}

void lvl_7(Model *model, UINT8 *game_state) {
   if (model->game_objects[6].bottom_right.x_pos < 0) {
        model->num_active_objects = 7;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,        OFFSET_64_UP_FROM_GROUND,  &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 84,   OFFSET_64_UP_FROM_GROUND,  &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 182,  OFFSET_64_UP_FROM_GROUND,  &(model->game_objects[3]), PLATFORM_SHORT);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 42,    OFFSET_32_UP_FROM_GROUND, &(model->game_objects[4]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 126, OFFSET_32_UP_FROM_GROUND,   &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 222,OFFSET_32_UP_FROM_GROUND,    &(model->game_objects[6]), TRIANGLE);
        (*game_state)++;
    }

}


void lvl_8(Model*model, UINT8 *game_state){
	 if (model->game_objects[6].bottom_right.x_pos < 0) {
        model->num_active_objects = 10;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,         OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +   84,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  182,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_SHORT);
		initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  192,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +   42,  OFFSET_64_UP_FROM_GROUND , &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  126,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[6]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  222,  OFFSET_64_UP_FROM_GROUND , &(model->game_objects[7]), TRIANGLE);
		 initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 302,  OFFSET_64_UP_FROM_GROUND , &(model->game_objects[8]), TRIANGLE);
		 initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 342,  OFFSET_64_UP_FROM_GROUND , &(model->game_objects[9]), TRIANGLE);
        (*game_state)++;
    }
	
	


}

void lvl_9(Model*model, UINT8 *game_state){
	 
    if(model->game_objects[9].bottom_right.x_pos < 0) {
        model->num_active_objects = 12;
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 ,OFFSET_38_UP_FROM_GROUND , &(model->game_objects[1]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[2]), TRIANGLE);
    
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 96, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 96, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_BRICK_1);

    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 128 , OFFSET_32_UP_FROM_GROUND, &(model->game_objects[5]), TRIANGLE);
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 192 ,OFFSET_48_UP_FROM_GROUND, &(model->game_objects[6]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 256 ,OFFSET_32_UP_FROM_GROUND , &(model->game_objects[7]), TRIANGLE);


    
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 288, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[8]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 320, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[9]), TRIANGLE);
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 384, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[10]), PLATFORM_BRICK_1);
	initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 384, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[11]), PLATFORM_BRICK_1);
        (*game_state)++;
        
    }


}

void lvl_10(Model*model, UINT8 *game_state) {
		if (model->game_objects[6].bottom_right.x_pos < 0) {
        model->num_active_objects = 10;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,         OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +   84,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  182,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_SHORT);
		initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  192,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +   42,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  126,  OFFSET_32_UP_FROM_GROUND, &(model->game_objects[6]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  222,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[7]), TRIANGLE);
		 initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 302,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[8]), TRIANGLE);
		 initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 342,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[9]), TRIANGLE);
        (*game_state)++;
    }
	
	
	
}




