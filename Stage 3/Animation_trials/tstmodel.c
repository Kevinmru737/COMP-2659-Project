#include <stdio.h>
#include "models.h"
#include "events.h"
#include "types.h"
#include "osbind.h"
#include "raster.h"
#include "types.h"

void print_full_player_location(Player* test_player);
void print_player(Player* test_player);

int main () {

    Player* test_player = create_player(250, 250);
    char user_input = 0;
    UINT16* base = Physbase();

    
    draw_horizontal_line(base, test_player->top_left.x_pos,
                                test_player->top_right.x_pos, test_player->top_left.y_pos, 32);

    while ((user_input = Cnecin()) != '\033'){
   
        if ((user_input) == ' ') {
            draw_horizontal_line(base, test_player->top_left.x_pos,
                                test_player->top_right.x_pos, test_player->top_left.y_pos, 32);
            jump(test_player);
            while (test_player->top_left.y_pos <= 250) {
                player_jumping(test_player);
                draw_horizontal_line(base, test_player->top_left.x_pos,
                                test_player->top_right.x_pos, test_player->top_left.y_pos, 32);
                Vsync();
                
                draw_horizontal_line(base, test_player->top_left.x_pos,
                                test_player->top_right.x_pos, test_player->top_left.y_pos, 32);
            }
            stop_jump(test_player);
            test_player->top_left.y_pos = 250;
            draw_horizontal_line(base, test_player->top_left.x_pos,
                                test_player->top_right.x_pos, test_player->top_left.y_pos, 32);
        }

    }
    
        

    print_player(test_player);
    

    return 0;
}

/*
    Prints the full location, meaning the x and y position of all vertices of the
    player.
*/

void print_full_player_location(Player* test_player) {
    printf("test_player x_pos = %i\n", test_player->top_left.x_pos);
    printf("test_player y_pos = %i\n", test_player->top_left.y_pos);
    printf("test_player top right x_pos = %i\n", test_player->top_right.x_pos);
    printf("test_player top right y_pos = %i\n", test_player->top_right.y_pos);
    printf("test_player bottom left x_pos = %i\n", test_player->bot_left.x_pos);
    printf("test_player bottom left y_pos = %i\n", test_player->bot_left.y_pos);
    printf("test_player bottom right x_pos = %i\n", test_player->bot_right.x_pos);
    printf("test_player bottom right y_pos = %i\n", test_player->bot_right.y_pos);
}
/*
    Prints the coordinates of the top left vertex of the player (the hotspot)
    as well as the state of the jumping condition and the vertical velocity.
*/
void print_player(Player* test_player) {
    printf("test_player x_pos = %i\n", test_player->top_left.x_pos);
    printf("test_player y_pos = %i\n", test_player->top_left.y_pos);
    printf("test_player is ");
    if (test_player->is_jumping == TRUE) {
        printf("jumping\n");
    }
    else {
        printf("not jumping\n");
    }
    printf("vert_vel = %i\n", test_player->vert_vel);
}

/*
    Prints the full location, meaning the x and y position of all vertices of a triangle.
*/
void print_full_triangle_location (Triangle* test_triangle) {
    
}

/*
    Prints the coordinates of the hotspot of the triangle as well as its horizontal
    velocity.
*/
void print_triangle(Triangle* test_triangle) {
    
}

/*
    Prints the full location, meaning the x and y position of all vertices of a platform.
*/
void print_full_platform_location (Platform* platform) {
    
}

/*
    Prints the coordinates of the hotspot of a platform as well as its horizontal
    velocity.
*/
void print_platform(Platform* platform) {
    
}

/*
    Prints the y position of the ground (the top edge of the ground).
*/
void print_ground(Ground* test_ground) {
    printf("The ground's y_pos is: %i", test_ground->y_pos);
}