
#include "Level.h"

LEVEL_UPDATE_FUNCTIONS lvl_update_functions[] = {
        lvl_1,
        lvl_2,
        lvl_3,
        lvl_4,
        lvl_5,
        lvl_6,
        lvl_7,
        lvl_8
};


void update_level(Model *model, UINT8 *game_state) {
    lvl_update_functions[(*game_state)](model, game_state);
}


void lvl_1(Model *model, UINT8* game_state) {
    model->num_active_objects = 1;
    initialize_game_object(160,271 - 31, &(model->game_objects[0]), PLAYER);
    initialize_ground( &( model->ground ) );
    (*game_state)++;

}
void lvl_2(Model*model, UINT8* game_state) {
        model->num_active_objects = 3;
        initialize_game_object(608,271 - 38 , &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(608 - 32,271 - 31 , &(model->game_objects[2]), TRIANGLE);
        (*game_state)++;

}

void lvl_3(Model *model, UINT8 *game_state) {
    if(model->game_objects[2].bottom_left.x_pos <= 480) {
        model->num_active_objects = 6;
        initialize_game_object(608,271 - 31 , &(model->game_objects[3]), PLATFORM_BRICK_1);
        initialize_game_object(608,271 - 31 -16, &(model->game_objects[4]), PLATFORM_SHORT);
        initialize_game_object(608 - 32,271 - 31 , &(model->game_objects[5]), TRIANGLE);
        (*game_state)++;
    }

}

void lvl_4(Model*model, UINT8* game_state) {
    if(model->game_objects[5].bottom_left.x_pos < 0) {
        model->num_active_objects = 6;
        initialize_game_object(608 - 32,271 - 68 , &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(608,271 - 68, &(model->game_objects[3]), PLATFORM_SHORT);
        initialize_game_object(608 - 32,271 - 31 , &(model->game_objects[4]), TRIANGLE);
        initialize_game_object(608 ,271 - 31 , &(model->game_objects[5]), TRIANGLE);
        (*game_state)++;
    }


}


void lvl_5(Model *model, UINT8 *game_state) {
    if(model->game_objects[5].bottom_left.x_pos < 0) {
        model->num_active_objects = 5;
        initialize_game_object(608, 200, &(model->game_objects[1]), PLATFORM_BRICK_2);
        initialize_game_object(608, 271-31, &(model->game_objects[2]), TRIANGLE);
        initialize_game_object(640, 160, &(model->game_objects[3]), TRIANGLE);
        initialize_game_object(672, 200, &(model->game_objects[4]), PLATFORM_1);
        (*game_state)++;
    }



}
void lvl_6(Model*model, UINT8 *game_state) {
    if (model->game_objects[4].bottom_left.x_pos < 0) {
        model->num_active_objects = 6;
        initialize_game_object(608, 271-31-16, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(608, 271 - 31, &(model->game_objects[2]), PLATFORM_BRICK_1);
        initialize_game_object(640, 271 - 31, &(model->game_objects[3]), TRIANGLE);
        initialize_game_object(672, 271 - 31, &(model->game_objects[4]), TRIANGLE);
        initialize_game_object(704, 271-31, &(model->game_objects[5]), PLATFORM_1);
        (*game_state)++;
    }

}void lvl_7(Model *model, UINT8 *game_state) {
    if (model->game_objects[5].bottom_left.x_pos < 0) {
        model->num_active_objects = 7;
        initialize_game_object(608,271 - 60, &(model->game_objects[1]), PLATFORM_SHORT);
        initialize_game_object(640,271 - 60, &(model->game_objects[2]), PLATFORM_SHORT);
        initialize_game_object(672,271 - 60, &(model->game_objects[3]), PLATFORM_SHORT);
        initialize_game_object(608,271 - 32 -60 , &(model->game_objects[4]), TRIANGLE);
        initialize_game_object(640,271 - 32 -60 , &(model->game_objects[5]), TRIANGLE);
        initialize_game_object(672,271 - 32 -60 , &(model->game_objects[6]), TRIANGLE);

        (*game_state)++;
    }


}
void lvl_8(Model*model, UINT8 *game_state){


}





