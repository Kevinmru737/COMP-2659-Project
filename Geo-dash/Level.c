
#include "Level.h"

/*
* Purpose: Serves as a single level sequnce in the game. 
           Each level is hardcoded. This should be called with other syncrhonous events.
           Updates model s used to a differnt sequence in a level.
*/
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
		lvl_10,
        lvl_11
};

/*Purpose: Calls the level sequence based on the game state*/
void update_level(Model *model, UINT8 *game_state) {
    lvl_update_functions[(*game_state)](model, game_state);
}

/*Purpose: First level sequcne, initializes the player and other objects*/
void lvl_1(Model *model, UINT8* game_state) {
    int offset = 512;
    model->num_active_objects = 16;

    initialize_game_object(PLAYER_START_X,PLAYER_START_Y, &(model->game_objects[PLAYER_INDEX]), PLAYER);
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
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +offset , OFFSET_64_UP_FROM_GROUND , &(model->game_objects[12]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset + 32, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[13]), PLATFORM_SHORT);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[14]), TRIANGLE);
    initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset + 32, OFFSET_32_UP_FROM_GROUND , &(model->game_objects[15]), TRIANGLE);
    (*game_state)++;
}

void lvl_2(Model*model, UINT8 *game_state){
    
    if (model->game_objects[15].bottom_right.x_pos < 0) {
        model->num_active_objects = 19;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 90, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[1]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 190, OFFSET_80_UP_FROM_GROUND + 2, &(model->game_objects[2]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 280, OFFSET_112_UP_FROM_GROUND, &(model->game_objects[3]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 90, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[4]),PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 190, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[5]),PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 190, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[6]),PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 280, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[7]),PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 280, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[8]),PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 280, OFFSET_96_UP_FROM_GROUND + 1, &(model->game_objects[9]),PLATFORM_BRICK_1);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 384, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[10]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 416, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[11]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 448, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[12]),PLATFORM_SHORT);


        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 352, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[13]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 480, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[14]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 512, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[15]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 544, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[16]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 576, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[17]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 550, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[18]),PLATFORM_SHORT);

        (*game_state)++;
    }
}


void lvl_3(Model*model, UINT8* game_state) {

  if(model->game_objects[18].bottom_right.x_pos < 0) {
        model->num_active_objects = 14;

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_38_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 50, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[2]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 150, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 300, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 400, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[5]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 500, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[6]), PLATFORM_BRICK_1);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 550, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[7]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 650, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[8]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 685, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[9]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 800, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[10]), PLATFORM_BRICK_2);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 850, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[11]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 900, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[12]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 950, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[13]), PLATFORM_SHORT);

        (*game_state)++;

    }

}

void lvl_4(Model *model, UINT8 *game_state) {

 if(model->game_objects[13].bottom_right.x_pos < 0) {
      model->num_active_objects = 19;
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_71_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_BRICK_2);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[2]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[3]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64, OFFSET_71_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_1);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 128, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[5]), PLATFORM_SHORT);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 212, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[6]), PLATFORM_SHORT);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 308, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[7]), PLATFORM_SHORT);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 398, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[8]), PLATFORM_SHORT);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 170, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[9]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 254, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[10]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 350, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[11]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 414, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[12]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 446, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[13]), TRIANGLE);


      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 500, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[14]), PLATFORM_SHORT);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 550, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[15]), TRIANGLE);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 650, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[16]), PLATFORM_BRICK_1);

      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 710, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[17]), PLATFORM_SHORT);
      initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 740, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[18]), TRIANGLE);

    (*game_state)++;
  }

}

void lvl_5(Model*model, UINT8* game_state) {

    if(model->game_objects[18].bottom_right.x_pos < 0) {
        model->num_active_objects = 15;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_71_UP_FROM_GROUND, &(model->game_objects[1]),PLATFORM_BRICK_2);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 50, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[2]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 150, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[3]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 100, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]),PLATFORM_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 150, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[5]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 200, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[6]),PLATFORM_SHORT);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 220, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[7]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 320, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[8]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 320, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[9]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 400, OFFSET_64_UP_FROM_GROUND,&(model->game_objects[10]), PLATFORM_SHORT);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 450, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[11]), PLATFORM_BRICK_2);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 510, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[12]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 510, OFFSET_64_UP_FROM_GROUND,&(model->game_objects[13]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 540, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[14]), TRIANGLE);
        (*game_state)++;
    }
}


void lvl_6(Model *model, UINT8 *game_state) {
    int offset = 180;
    if (model->game_objects[14].bottom_right.x_pos < 0) {
        model->num_active_objects = 12;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_48_UP_FROM_GROUND, &(model->game_objects[1]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[2]),PLATFORM_BRICK_1);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[3]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[4]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 64, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[5]),PLATFORM_1);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset, OFFSET_64_UP_FROM_GROUND - 20,&(model->game_objects[6]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset + 32, OFFSET_64_UP_FROM_GROUND - 20,&(model->game_objects[7]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset + 64, OFFSET_64_UP_FROM_GROUND - 20,&(model->game_objects[8]), PLATFORM_SHORT);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset, OFFSET_90_UP_FROM_GROUND - 20,&(model->game_objects[9]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset + 32, OFFSET_90_UP_FROM_GROUND - 20,&(model->game_objects[10]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + offset + 64, OFFSET_90_UP_FROM_GROUND - 20,&(model->game_objects[11]), TRIANGLE);
        (*game_state)++;

    }


}
void lvl_7(Model*model, UINT8 *game_state) {

    if (model->game_objects[11].bottom_right.x_pos < 0) {
        model->num_active_objects = 9;

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[1]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 100, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 200, OFFSET_90_UP_FROM_GROUND, &(model->game_objects[3]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 300, OFFSET_90_UP_FROM_GROUND - 30,&(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 400, OFFSET_90_UP_FROM_GROUND - 60,&(model->game_objects[5]), PLATFORM_SHORT);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 70, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[6]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 200, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[7]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 450, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[8]),TRIANGLE);
        (*game_state)++;
    }
}



void lvl_8(Model *model, UINT8 *game_state) {
    if (model->game_objects[8].bottom_right.x_pos < 0) {
        model->num_active_objects = 17;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 110, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 220, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[3]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 330, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 440, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[5]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 550, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[6]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 660, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[7]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 770, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[8]),PLATFORM_SHORT);


        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 50, OFFSET_32_UP_FROM_GROUND, &(model->game_objects[9]),TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 150, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[10]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 260, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[11]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 370, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[12]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 480, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[13]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 580, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[14]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 700, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[15]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 810, OFFSET_32_UP_FROM_GROUND,&(model->game_objects[16]), TRIANGLE);
    

        (*game_state)++;
    }

}


void lvl_9(Model*model, UINT8 *game_state){
	 
    if(model->game_objects[17].bottom_right.x_pos < 0) {
        model->num_active_objects = 14;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 32, OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]),PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[3]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  130,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  162,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[5]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 162,  OFFSET_96_UP_FROM_GROUND, &(model->game_objects[6]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  162,  OFFSET_144_UP_FROM_GROUND - 16, &(model->game_objects[7]), PLATFORM_BRICK_2);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 240,  OFFSET_32_UP_FROM_GROUND, &(model->game_objects[8]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  240,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[9]), PLATFORM_SHORT);
		
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 300,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[10]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  300,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[11]), PLATFORM_SHORT);

        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 + 450,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[12]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  400,  OFFSET_96_UP_FROM_GROUND, &(model->game_objects[13]), PLATFORM_SHORT);
    
        (*game_state)++;
        
    }
}

void lvl_10(Model*model, UINT8 *game_state) {
		if (model->game_objects[13].bottom_right.x_pos < 0) {
        model->num_active_objects = 8;
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32,         OFFSET_64_UP_FROM_GROUND, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +   84,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  182,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[3]), PLATFORM_SHORT);
		initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  192,  OFFSET_64_UP_FROM_GROUND, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +   42,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  126,  OFFSET_32_UP_FROM_GROUND, &(model->game_objects[6]), TRIANGLE);
        initialize_game_object(SCREEN_RIGHT_EDGE_FOR_32_X_32 +  222,  OFFSET_32_UP_FROM_GROUND , &(model->game_objects[7]), TRIANGLE);
	
        (*game_state)++;
    }
	
	
	
}

/*final sequence, waits for the last platform to pass*/
void lvl_11(Model*model, UINT8 *game_state) {
		if (model->game_objects[7].bottom_right.x_pos < 0) {
        (*game_state)++;
    }
	
	
}


