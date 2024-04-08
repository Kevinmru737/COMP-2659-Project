#include <osbind.h>
#include "events.h"
#include "render.h"


int main () {
    Model uninit_model;
    Model* test_model = &uninit_model;
    UINT32* base = Physbase();
    int player_start_x = 160;
    int touching_ground_y = 240;
    int ground_start_y = 272;
    int triangle_1_x = 200;
    int triangle_2_x = 250;
    int platform_1_x = 300;
    int platform_2_x = 400;
    int platform_1_y = 200;
    int platform_2_y = 150;
    int obstacle_velocity = 2;
    int curr_num_triangles = 0;
    int curr_num_platforms = 0;

    test_model->num_active_players = 1;
    test_model->num_active_triangles = 2;
    test_model->num_active_platforms = 2;

    initialize_player(player_start_x, touching_ground_y, &test_model->player[0]);
    initialize_ground(ground_start_y, &test_model->ground);
    initialize_triangle(triangle_1_x, touching_ground_y, obstacle_velocity,
                        &test_model->triangles[0]);

    initialize_triangle(triangle_2_x, touching_ground_y, obstacle_velocity,
                        &test_model->triangles[1]);

    initialize_platform(platform_1_x, platform_1_y, 64, 32, obstacle_velocity,
                        &test_model->platform[0]);

    initialize_platform(platform_2_x, platform_2_y, 64, 32, obstacle_velocity,
                        &test_model->platform[1]);

        
    render(test_model, base);


       
    

    

    return 0;
}