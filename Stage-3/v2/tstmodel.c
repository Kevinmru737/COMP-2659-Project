#include <stdio.h>
#include "models.h"
#include "events.h"
#include "types.h"
#include "osbind.h"


void print_full_triangle_details(Triangle* test_triangle);
void print_full_player_details(Player* test_player);
void print_ground(Ground* test_ground);
void print_full_platform_details(Platform* test_platform);

int main () {

   Model  model;

    initialize_player(45,32,&(model.player[0]),0);

    print_full_player_details(&model.player[0]);

    initialize_ground(3, &model.ground);

    print_ground(&model.ground);

    initialize_platform(32,399,64,3,3,&(model.platform[0]));

    print_full_platform_details(&model.platform[0]);

    initialize_triangle(63,63,64,&model.triangles[0]);

    print_full_triangle_details(&model.triangles[0]);

    if(player_triangle_collison(&model.player[0],&model.triangles[0]) == TRUE)
    {
        printf("here \n");
    }
   





    return 0;
}




/*Author : Kevin
* Purpose:  Prints the full location, meaning the x and y position of all vertices of the
*            player. Also prints whether it is jumping or not and the vetical velocity
*/

void print_full_player_details(Player* test_player) {
    printf("test_player top left x_pos = %i\n", test_player->top_left.x_pos);
    printf("test_player y_pos = %i\n", test_player->top_left.y_pos);
    printf("test_player top right x_pos = %i\n", test_player->top_right.x_pos);
    printf("test_player top right y_pos = %i\n", test_player->top_right.y_pos);
    printf("test_player bottom left x_pos = %i\n", test_player->bot_left.x_pos);
    printf("test_player bottom left y_pos = %i\n", test_player->bot_left.y_pos);
    printf("test_player bottom right x_pos = %i\n", test_player->bot_right.x_pos);
    printf("test_player bottom right y_pos = %i\n", test_player->bot_right.y_pos);

    printf("test_player is ");
    if (test_player->is_jumping == TRUE) {
        printf("jumping\n");
    }
    else {
        printf("not jumping\n");
    }

    printf("test_player vertical velocity is : %i\n", test_player->vert_vel);


}



/*
    Prints the full location, meaning the x and y position of all vertices of a triangle.
*/
void print_full_triangle_details(Triangle* test_triangle) {

    printf("test_triangle top vertex x_pos = %i\n", test_triangle->top.x_pos);
    printf("test_triangle top vertex y_pos = %i\n", test_triangle->top.y_pos);

    printf("test_triangle bottom left vertex x_pos = %i\n", test_triangle->bot_left.x_pos);
    printf("test_triangle bottom left vertex y_pos = %i\n", test_triangle->bot_left.y_pos);

    printf("test_triangle bottom right vertex x_pos = %i\n", test_triangle->bot_right.x_pos);
    printf("test_triangle bottom right vertex y_pos = %i\n", test_triangle->bot_right.y_pos);

    printf("test_triangle horizontal velocity  = %i\n", test_triangle->hor_vel);





}


/*
    Prints the full location, meaning the x and y position of all vertices of a platform.
*/
void print_full_platform_details(Platform* test_platform) {
    printf("test_platform top left x_pos = %i\n", test_platform->top_left.x_pos);
    printf("test_platform y_pos = %i\n", test_platform->top_left.y_pos);
    printf("test_platform top right x_pos = %i\n", test_platform->top_right.x_pos);
    printf("test_platform top right y_pos = %i\n", test_platform->top_right.y_pos);
    printf("test_platform bottom left x_pos = %i\n", test_platform->bot_left.x_pos);
    printf("test_platform bottom left y_pos = %i\n", test_platform->bot_left.y_pos);
    printf("test_platform bottom right x_pos = %i\n", test_platform->bot_right.x_pos);
    printf("test_platform bottom right y_pos = %i\n", test_platform->bot_right.y_pos);
    printf("test_platform vertical velocity is : %i\n", test_platform->hor_vel);

}


/*
    Prints the y position of the ground (the top edge of the ground).
*/
void print_ground(Ground* test_ground) {
    printf("The ground's y_pos is: %i", test_ground->y_pos);
}