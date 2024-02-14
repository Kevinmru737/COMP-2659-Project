#include <stdio.h>
#include "models.h"
#include "events.h"
#include "types.h"
#include "osbind.h"

void print_full_player_location(Player* test_player);
void print_player(Player* test_player);
void print_ground(Ground* test_ground);

int main () {

   Model model;

   initialize_player(32,32,&model.player);
   initialize_ground(model.player.bot_right.y_pos+1,&model.ground);

   print_full_player_location(&model.player);
   printf("%d \n",(model.ground.y_pos));

   print_ground(&model.ground);
   
   
    /*
    Ground uninit_ground;
    Player uninit_player;
    Platform uninit_platform;

    Ground* test_ground = &uninit_ground;
    Player* test_player = &uninit_player;
    Platform* test_platform = &uninit_platform;
    char user_input = 0;

    initialize_player(272, 241, test_player);
    initialize_ground(272, test_ground);
    initialize_platform(300, 250, 50, 30, 1, test_platform);

    print_player(test_player);
    while ((user_input = Cnecin()) != '\033'){

        if ((user_input) == ' ') {
            jump_request(test_player);
            printf("player jumped\n");
            print_player(test_player);
        }

        if ((user_input) == 'p') {
            while(platform_collision_unsafe(test_player, test_platform) == FALSE) {
                printf("platform x pos:%i", test_platform->top_left.x_pos);
                platform_moving(test_platform);
            }
            
        }

        while (test_player->is_jumping == TRUE) {
            
            player_jumping(test_player);
            printf("player jumping\n");
            
            if(ground_collision(test_player, test_ground) == TRUE) {
                stop_jump(test_player);
                printf("ground collision detected\n");
                printf("ground y pos %i: ", test_ground->y_pos);
                printf("player bot-left y pos %i: ", test_player->bot_left.y_pos);
                print_player(test_player);
            }
        }
        
    }
    
        

    print_player(test_player);
 */   

    return 0;
}

/*
    Prints the full location, meaning the x and y position of all vertices of the
    player.
*/

void print_full_player_location(Player* test_player) {
    printf("test_player top left x_pos = %i\n", test_player->top_left.x_pos);
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