#include "tstmdl.h"




int main () {

    test_player_initializer();
    test_triangle_initializer();
    test_player_jump();


    return 0;
}







/* Author: Depanshu
* Purpose: Tests the player initializer function in model.h
*
*  Test Cases:
*             Case 1: Testing a common initialization. Initializes player starting at y= 32, y = 33 and vert velocity = 4. 
*             Case 2: Initializes multiple players.
*
* Note: More test cases could not be done due to time constraints
*
*/
void test_player_initializer() {
    Model  model;
    bool test_passed = TRUE;

    int player_x = 32;
    int player_y = 33;
    int player_vert = 4;

    printf("\n\nTESTING PLAYER INITIALIZER IN Model.h\n \n");
    wait_for_user();


    printf("Testing a common initialization \n");
    printf("Case 1: Initializes Player starting at y= 32, y = 33 and vert velocity = 4\n");
    wait_for_user();
    initialize_player(player_x, player_y, &model.player[0], player_vert);


    /* Check if the player's properties match the expected values, the player wil 32 x 32*/
    if (model.player[0].top_left.x_pos != player_x || model.player[0].top_left.y_pos != player_y ||
        model.player[0].vert_vel != player_vert || model.player[0].top_right.x_pos != player_x + 31 ||
        model.player[0].top_right.y_pos != player_y || model.player[0].bot_left.x_pos != player_x || 
        model.player[0].bot_left.y_pos != player_y + 31 || model.player[0].bot_right.x_pos != player_x + 31 ||
        model.player[0].bot_right.y_pos != player_y + 31) {

        test_passed = FALSE;
    }
    
    printf("%s\n", test_passed == TRUE ? "Test Passed" : "Test Failed");
    printf("Player details: \n");
    wait_for_user();

    print_full_player_details(&(model.player[0]));
    wait_for_user();


    printf("\n\nCase 2: Initializes multiple players. First player already initialized,\n");
    printf("initializing second player at x = 100 , y = 111 and velocity = 6\n");

    wait_for_user();
    test_passed = TRUE;
    player_x = 100;
    player_y = 111;
    player_vert = 6;

    initialize_player(player_x, player_y, &model.player[1], player_vert);

    if (model.player[1].top_left.x_pos != player_x || model.player[1].top_left.y_pos != player_y ||
        model.player[1].vert_vel != player_vert || model.player[1].top_right.x_pos != player_x + 31 ||
        model.player[1].top_right.y_pos != player_y || model.player[1].bot_left.x_pos != player_x || 
        model.player[1].bot_left.y_pos != player_y + 31 || model.player[1].bot_right.x_pos != player_x + 31 ||
        model.player[1].bot_right.y_pos != player_y + 31) {

        test_passed = FALSE;
    }

    printf("%s\n", test_passed == TRUE ? "Test Passed" : "Test Failed");
    printf("Second player details: \n");
    wait_for_user();
    print_full_player_details(&(model.player[1]));

}

/**
* Author: Depanshu
* Purpose: Tests the triangle initializer function defined in model.h.
* 
* Test Cases:
* Case 1: Verifies the initliazer initializes with correcty with the given input parameters. Checking
*         that all vertices (bottom left, top, and bottom right) are correctly positioned
*         relative to the hot spot
* 
* Case 2: Testing with differnt input parameters
* 
* Note: More test cases could not be done due to time constraints
*
*/
void test_triangle_initializer() {
    Model model;
    bool test_passed = TRUE;


    int triangle_x = 50;
    int triangle_y = 60;
    int triangle_vel = 3;

    printf("\n\nTESTING TRIANGLE INITIALIZER in model.h\n\n");
    wait_for_user();

   
    printf("Case 1: Common Initialization of a Triangle at x=50, y=60 with velocity=3\n");
    wait_for_user();
    initialize_triangle(triangle_x, triangle_y, triangle_vel, &model.triangles[0]);

    if (model.triangles[0].bot_left.x_pos != triangle_x || model.triangles[0].bot_left.y_pos != triangle_y + 31 ||
        model.triangles[0].top.x_pos != triangle_x + 15 || model.triangles[0].top.y_pos != triangle_y ||
        model.triangles[0].bot_right.x_pos != triangle_x + 31 || model.triangles[0].bot_right.y_pos != triangle_y + 31 ||
        model.triangles[0].hor_vel != triangle_vel) {
        test_passed = FALSE;
    }

    printf("%s\n", test_passed == TRUE ? "Test Passed" : "Test Failed");
    printf("Triangle details: \n");
    wait_for_user();
    print_full_triangle_details(&model.triangles[0]);
    wait_for_user();

    
    test_passed = TRUE; 
    triangle_x = 100;
    triangle_y = 120;
    triangle_vel = 5;

    printf("\n\nCase 2: Initializing another Triangle at different position and velocity. x = 100 , y = 120 and velocity = 5\n");
    initialize_triangle(triangle_x, triangle_y, triangle_vel, &model.triangles[1]);

    if (model.triangles[1].bot_left.x_pos != triangle_x || model.triangles[1].bot_left.y_pos != triangle_y + 31 ||
        model.triangles[1].top.x_pos != triangle_x + 15 || model.triangles[1].top.y_pos != triangle_y ||
        model.triangles[1].bot_right.x_pos != triangle_x + 31 || model.triangles[1].bot_right.y_pos != triangle_y + 31 ||
        model.triangles[1].hor_vel != triangle_vel) {
        test_passed = FALSE;
    }

    printf("%s\n", test_passed ? "Test Passed" : "Test Failed");
    printf("Triangle details: \n");
    wait_for_user();
    print_full_triangle_details(&model.triangles[1]);

}



/* Author: Depanshu
*  Purpose: Tests the jump functionality for a player in the game model.
*
* Note: 
*/
void test_player_jump() {

  
}









/* Author: Depanshu
*  Purpose: Tests the movement  functionality for a player in the game model.
*
* Note:
*/
void test_player_move() {


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

/*
*Author :Depanshu Suyal
*Purpose:  Pauses the program execution until a key is pressed.
*/
void wait_for_user() {
    while (!Cconis()) {
    }
     Cnecin(); 

}
