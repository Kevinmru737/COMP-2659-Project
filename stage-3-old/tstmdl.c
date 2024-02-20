/* Overview:
*           Test driver for various functionality for the events and model module.
*           
*/

#include "tstmdl.h"




int main () {
/*
    test_player_initializer();
    test_triangle_initializer();
    test_platform_initializer();
    tst_triangle_movement();
    tst_platform_movement();
    tst_player_movement();
  */  
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

    printf("\n*** Player Initializer Test ***\n");
    printf("This test checks the player initialization process.\n\n");
    printf("Press any key to begin...\n");
    wait_for_user();
   
    printf("Test Case 1: Common Player Initialization\n");
    printf("Initializing Player at X = %d, Y = %d with Vertical Velocity = %d\n\n", player_x, player_y, player_vert);
    printf("Press any key to initialize...\n");
    wait_for_user();


    initialize_player(player_x, player_y, &model.player[0], player_vert);

    if (model.player[0].top_left.x_pos != player_x || model.player[0].top_left.y_pos != player_y ||
        model.player[0].vert_vel != player_vert || model.player[0].top_right.x_pos != player_x + 31 ||
        model.player[0].top_right.y_pos != player_y || model.player[0].bot_left.x_pos != player_x || 
        model.player[0].bot_left.y_pos != player_y + 31 || model.player[0].bot_right.x_pos != player_x + 31 ||
        model.player[0].bot_right.y_pos != player_y + 31) {
        test_passed = FALSE;
    }

    printf("Result: %s\n", test_passed == TRUE ? "SUCCESS - Player correctly initialized" : "FAILURE - Incorrect Player Initialization");
    printf("Player State:\n");
    printf("Press any key to display details...\n");
    wait_for_user();
    print_full_player_details(&model.player[0]);



    /**************************Case 2*************************************/

    
    test_passed = TRUE;
    player_x = 100;
    player_y = 111;
    player_vert = 6;

    printf("\nTest Case 2: Initializing a second player. One was already initialized in test 1\n");
    printf("Initializing second player at X = %d, Y = %d with Vertical Velocity = %d\n\n", player_x, player_y, player_vert);
    printf("Press any key to display details...\n");
    wait_for_user();

    initialize_player(player_x, player_y, &model.player[1], player_vert);


    if (model.player[1].top_left.x_pos != player_x      || model.player[1].top_left.y_pos != player_y       ||
        model.player[1].vert_vel != player_vert         || model.player[1].top_right.x_pos != player_x + 31 ||
        model.player[1].top_right.y_pos != player_y     || model.player[1].bot_left.x_pos != player_x       || 
        model.player[1].bot_left.y_pos != player_y + 31 || model.player[1].bot_right.x_pos != player_x + 31 ||
        model.player[1].bot_right.y_pos != player_y + 31 ) {
        test_passed = FALSE;
    }

    printf("Result: %s\n", test_passed == TRUE ? "SUCCESS - Second player correctly initialized." : "FAILURE - Second Player Incorrectly Initialized.");
    printf("Second Player Details:\n");
    printf("Press any key to display details...\n");
    wait_for_user();
    print_full_player_details(&model.player[1]);


}





/**
* Author: Depanshu
* Purpose: Tests the triangle initializer function defined in model.h.
* 
* Test Cases:
* Case 1: Verifies the initliazer initializes correcty with the given input parameters. Checking
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

    printf("\n*** Triangle Initializer Test ***\n");
    printf("This test verifies the correct initialization of triangles within a model.\n\n");
    printf("Press any key to begin...\n");
    wait_for_user();

    printf("Test Case 1: Initializing a triangle\n");
    printf("Location: x=50, y=60 with velocity=3\n\n");
    printf("Press any key to initialize...\n");
    wait_for_user();

    initialize_triangle(triangle_x, triangle_y, triangle_vel, &model.triangles[0]);


    if (model.triangles[0].bot_left.x_pos != triangle_x       || model.triangles[0].bot_left.y_pos != triangle_y + 31  ||
        model.triangles[0].top.x_pos != triangle_x + 15       || model.triangles[0].top.y_pos != triangle_y            ||
        model.triangles[0].bot_right.x_pos != triangle_x + 31 || model.triangles[0].bot_right.y_pos != triangle_y + 31 ||
        model.triangles[0].hor_vel != triangle_vel) {

            test_passed = FALSE;
   
    }

    printf("Outcome: %s\n", test_passed == TRUE ? "SUCCESS - Triangle initialized correctly." : "FAILURE - Triangle initialization incorrect.");
    printf("Triangle State:\n");
    printf("Press any key to display details...\n");
    wait_for_user();
    print_full_triangle_details(&model.triangles[0]);


    /**************************Case 2*************************************/


    test_passed = TRUE;
    triangle_x = 100;
    triangle_y = 120;
    triangle_vel = 5;


    printf("\nTest Case 2: Initializing another triangle at a new position and velocity\n");
    printf("Location: x=100, y=120 with velocity=5\n\n");
    printf("Press any key to initialize...\n");
    wait_for_user();

    initialize_triangle(triangle_x, triangle_y, triangle_vel, &model.triangles[1]);



    if (model.triangles[1].bot_left.x_pos != triangle_x       || model.triangles[1].bot_left.y_pos != triangle_y + 31  ||
        model.triangles[1].top.x_pos != triangle_x + 15       || model.triangles[1].top.y_pos != triangle_y            ||
        model.triangles[1].bot_right.x_pos != triangle_x + 31 || model.triangles[1].bot_right.y_pos != triangle_y + 31 ||
        model.triangles[1].hor_vel != triangle_vel) {

            test_passed = FALSE;
    
    }

    printf("Outcome: %s\n", test_passed ? "SUCCESS - Triangle initialized correctly." : "FAILURE - Triangle initialization incorrect.");
    printf("Triangle State:\n");
    printf("Press any key to display details...\n");
    wait_for_user();
    print_full_triangle_details(&model.triangles[1]);

}



/**
* Author: Depanshu
* Purpose: Tests the platform initializer function defined in model.h.
* 
* Test Cases:
* Case 1: Verifies the initliazer initializes correctly  with the given input parameters. Checking
*         that all vertices (bottom left, bottom right ,etc) are correctly positioned
* 
* 
* Note: More test cases could not be done due to time constraints
*
*/
void test_platform_initializer() {
    Model  model;
    bool test_passed = TRUE;

    int platform_x = 32;
    int platform_y = 33;
    int platform_vel = 4;
    int platform_height = 2;
    int platform_width = 64;

    printf("\n*** Platform Initializer Test ***\n");
    printf("This test checks the Platform initialization process.\n\n");
    printf("Press any key to begin...\n");
    wait_for_user();
   
    printf("Test Case 1: Common Platform Initialization\n");
    printf("Initializing Platform at\n X = %d, Y = %d, Height = %d, Width = %d and  Horizontal Velocity = %d\n\n", platform_x, platform_y, platform_height, platform_width, platform_vel);
    printf("Press any key to initialize...\n");
    wait_for_user();

    initialize_platform(platform_x,platform_y, platform_width, platform_height, platform_vel, &model.platform[0]);


    /*Validates platform's positions, size, and velocity against expected values */
   if(model.platform[0].top_left.x_pos != platform_x                        ||   model.platform[0].top_left.y_pos != platform_y                        ||
     model.platform[0].top_right.x_pos != platform_x + platform_width -1    ||   model.platform[0].top_right.y_pos != platform_y                       ||
     model.platform[0].bot_left.x_pos != platform_x                         ||   model.platform[0].bot_left.y_pos != platform_y + platform_height - 1  ||
     model.platform[0].bot_right.x_pos != platform_x + platform_width -1    ||   model.platform[0].bot_right.y_pos != platform_y +  platform_height -1 ||
     model.platform[0].hor_vel != platform_vel ) {
            test_passed = FALSE;
    }

    printf("Result: %s\n", test_passed == TRUE ? "SUCCESS - Platform correctly initialized" : "FAILURE - Incorrect Platform Initialization");
    printf("Platform State:\n");
    printf("Press any key to display details...\n");
    wait_for_user();
    print_full_platform_details(&model.platform[0]);



}


/* Author: Depanshu 
*  Purpose: Tests the movement functionalities for triangles in events.h
*
* Details: This will be a synchronous event. Every clock tick, all active triangles will
*           move across the horizotal axis.
*
* Test Cases:
*           Case 1: Verifies that a single triangle moves horizontally according to its initialized velocity
*
*           Case 2: Tests the simultaneous movement of multiple triangles with different initial positions,
*           and velocities,
*   
* Note:     These test cases should cover all edge cases. The move_all_triangle function does not do any
*           bounds checking. Case 2 only used 3 triangles when the max number of triangles at a time is 10,
*           because the output to console would have been very confusing.
*/
void tst_triangle_movement() {
    Model model;
    char user_input;
    int i = 0;


    printf("\n*** Triangle Movement Test ***\n\n");
    printf("Description:\n");
    printf("This test simulates the horizontal movement (right to left) of active triangles.\n");
    printf("Each triangle moves according to its initialized velocity.\n\n");

    printf("Press any key to start the tests...\n");
    wait_for_user();

    /************Case 1*************************/

    printf("Test Case 1: Single Triangle Movement\n\n");

    initialize_triangle(640, 22, 3, &model.triangles[0]);
    model.num_active_triangles = 1;

    printf("Initial Triangle State:\n");
    print_full_triangle_details(&model.triangles[0]);


    printf("\nInstructions:\n");
    printf("Press the space bar to move the triangle left.\n");
    printf("Press ESC to end this test.\n\n");


    printf("Expected Behavior:\n");
    printf("With each space bar press, the triangle's vertices' X positions will decrease by its horizontal velocity.\n");
    printf("The Y positions will remain unchanged.\n\n");


    while ((user_input = Cnecin()) != '\033') { /*Escape key code*/
        if (user_input == ' ') {
            move_all_active_triangles(&model);
            printf("Triangle Movement Detected. Current State:\n");
            print_full_triangle_details(&model.triangles[0]);
        }
    }


/****************************Case 2*************************************/

    printf("Test 2: Moving multiple triangles at differnt X, Y and Velocities\n\n");
    printf("Press any key to start the test...\n");
    wait_for_user();

    initialize_triangle(333, 25, 5, &model.triangles[0]);
    initialize_triangle(500, 100, 2, &model.triangles[1]);
    initialize_triangle(200, 150, 4, &model.triangles[2]);

    model.num_active_triangles = 3;

    printf("Initial triangle details for all 3 active triangles:\n");
    for (i; i < model.num_active_triangles; i++) {
        printf("Triangle %d details:\n", i + 1);
        print_full_triangle_details(&model.triangles[i]);
    }


    printf("\nInstructions:\n");
    printf("Press the space bar to move the triangle left.\n");
    printf("Press ESC to end this test.\n\n");
    printf("Each triangle's vertices' x position should keep decreasing by its horizontal velocity. Y position should be constant\n\n");

    printf("Press any key to start the test...\n");
    wait_for_user();

    while ((user_input = Cnecin()) != '\033') { 
        if (user_input == ' ') {
            move_all_active_triangles(&model);
            printf("Triangles moved\n");
            for (i = 0; i < model.num_active_triangles; i++) {
                printf("Triangle %d details:\n", i + 1);
                print_full_triangle_details(&model.triangles[i]);
            }
        }
    }
  


}








/* Author: Depanshu 
*  Purpose: Tests the movement functionalities for platforms in events.h
*
* Details: This will be a synchronous event. Every clock tick, all active paltfroms will
*           move across the horizotal axis.
*
* Test Cases:
*           Case 1: Verifies that a single platform moves horizontally according to its initialized velocity
*
*           Case 2: Tests the simultaneous movement of multiple platforms with different initial positions, dimensions
*           and velocities.
*   
* Note:     These test cases should cover all edge cases. The move_all_active_platforms function does not do any
*           bounds checking. Case 2 only used 3 platforms when the max number of platforms at a time is 10,
*           because the output to console would have been very confusing.
*/
void tst_platform_movement() {

    Model model;
    char user_input;
    int i = 0;

    printf("\n*** Platform Movement Test ***\n\n");
    printf("Description:\n");
    printf("This test simulates the horizontal movement (right to left) of active platforms.\n");
    printf("Each platform moves according to its initialized velocity.\n\n");

    printf("Press any key to start the tests...\n");
    wait_for_user();


    /**************Case 1**********************/
    
    printf("Test Case 1: Single platform Movement\n\n");

    initialize_platform(640, 22, 32, 2, 5, &model.platform[0]);
    model.num_active_platforms = 1;

    printf("Initial Platform State:\n");
    print_full_platform_details(&model.platform[0]);

    printf("\nInstructions:\n");
    printf("Press the space bar to move the platform left.\n");
    printf("Press ESC to end this test.\n\n");

    printf("Expected Behavior:\n");
    printf("With each space bar press, the platform's vertices' X positions will decrease by its horizontal velocity.\n");
    printf("The Y positions will remain unchanged.\n\n");


    while ((user_input = Cnecin()) != '\033') { /*Escape key code*/
        if (user_input == ' ') {
            move_all_active_platforms(&model);
            printf("Platform Movement Detected. Current State:\n");
            print_full_platform_details(&model.platform[0]);
        }
    }


/*************************************Case 2**********************************************/

    printf("Test 2: Moving multiple platforms at differnt X, Y, width, height and velocities\n\n");
    printf("Press any key to start the test...\n");
    wait_for_user();

    initialize_platform(640, 22, 32,2, 1, &model.platform[0]);
    initialize_platform(333, 33, 64, 3, 4, &model.platform[1]);
    initialize_platform(222, 56, 128, 5, 6, &model.platform[2]);

    model.num_active_platforms = 3;

    printf("Initial Platform details for all 3 active platforms:\n");

    for (i; i < model.num_active_platforms; i++) {
        printf("Platforms %d details:\n", i + 1);
        print_full_platform_details(&model.platform[i]);
    }
    
    printf("\nInstructions:\n");
    printf("Press the space bar to move the platforms left.\n");
    printf("Press ESC to end this test.\n\n");
    printf("Each platforms's vertices' x position should keep decreasing by its horizontal velocity. Y position should be constant\n\n");
    
    printf("Press any key to start the test...\n");
    wait_for_user();

    while ((user_input = Cnecin()) != '\033') { 
        if (user_input == ' ') {
            move_all_active_platforms(&model);
            printf("Platforms moved\n");
            for (i = 0; i < model.num_active_platforms; i++) {
                printf("Platforms %d details:\n", i + 1);
                print_full_platform_details(&model.platform[i]);
            }
        }

    }

}




/* Author: Depanshu
* Purpose: Tests the vertical movement functionality of player cube
*
* Test Cases:
*          Case 1: Ground-based Jump - Verifies that the player's jump initiates correctly when on the ground, and that
*                  subsequent 'clock ticks' simulate gravity affecting the player's vertical movement until landing.
*
*          Case 2: Platform-based Jump - Similar to case 1, but this the player jumps from the top of a surface
*
*/

void tst_player_movement() {
    Model model;
    char user_input;
    printf("\n*** Player Movement Test ***\n"
            "Description: This test simulates the vertical movement of the active player. "
            "The player moves anytime it is not in contact with either the ground or a platform.\n"
            "\nPress any key to start the tests...\n");
    wait_for_user();

    printf("Test Case 1: Ground-based Jump\n"
            "Instructions: Press the space bar to jump. Press 'c' to simulate a clock tick and print the player's position. "
            "Press ESC to end this test.\n");
    
    
    initialize_player(640, 22, &model.player[0], 0);
    initialize_ground(model.player[0].bot_left.y_pos, &model.ground);
    model.num_active_players = 1;
    
    
     printf("Press any key to start the test...\n"); 
    wait_for_user();

    printf("Expected Behavior: Player's vertical velocity changes with each space bar press, simulating a jump. "
        "Velocity decreases each frame until the player lands.\n\n");
    
    printf("Initial Player State:\n");
    print_full_player_details(&model.player[0]);
    printf("Press any key to start the test...\n\n");


    while ((user_input = Cnecin()) != '\033') { 
        if (user_input == ' ') {
            printf("Jump initiated. 'c' to tick, 't' to exit.\n");
            jump_request(&model, 0);
            while ((user_input = Cnecin()) != 't') {
                if (user_input == 'c') {
                    move_all_active_players(&model);
                    print_full_player_details(&(model.player[0]));
                    printf(" 'c' to tick, 't' to exit.\n");
                }
            }
            printf("Jump sequence exited. Press ESC to exit or space to initiate another jump \n");
        }
    }

    /*************************************Case 2**********************************************/

    printf("Test Case 2: Platform-based Jump\n"
        "Instructions: Similar to Test Case 1, but with the player starting on a platform.\n");
    
    initialize_player(640, 33, &model.player[0], 0);
    initialize_platform(629, model.player[0].bot_left.y_pos, 32, 2, 0, &model.platform[0]);
    
    model.ground.y_pos = 999; /* so that it dosent interefere*/
    model.num_active_players = 1;
    model.num_active_platforms = 1;

    printf("Press any key to start the test...\n");
    wait_for_user();

    printf("Expected Behavior: Similar to Test Case 1, but the player lands on the platform's top edge.\n\n");
    printf("Initial Player State:\n");
    print_full_player_details(&model.player[0]);
    printf("Initial Platform State:\n");
    print_full_platform_details(&model.platform[0]);
    printf("Press any key to start the test...\n\n");

    while ((user_input = Cnecin()) != '\033') { 
        if (user_input == ' ') {
            printf("Jump initiated. Press 'c' to mock a clock tick, and 't' to exit.\n");
            jump_request(&model, 0);
            while ((user_input = Cnecin()) != 't') {
                if (user_input == 'c') {
                    move_all_active_players(&model);
                    print_full_player_details(&(model.player[0]));
                    printf(" Press 'c' to mock a clock tick, and 't' to exit.\n");
                }
            }
            printf("Jump sequence exited. Press ESC to exit or space to initiate another jump \n");
        }
    }

}







/* Author :  Kevin
*  Purpose:  Prints the full location, meaning the x and y position of all vertices of the
*            player. Also prints whether it is jumping or not and the vetical velocity
*/

void print_full_player_details(Player* test_player) {
printf("Top Left Vertex:        X = %i, Y = %i\n", test_player->top_left.x_pos, test_player->top_left.y_pos);
printf("Top Right Vertex:       X = %i, Y = %i\n", test_player->top_right.x_pos, test_player->top_right.y_pos);
printf("Bottom Left Vertex:     X = %i, Y = %i\n", test_player->bot_left.x_pos, test_player->bot_left.y_pos);
printf("Bottom Right Vertex:    X = %i, Y = %i\n", test_player->bot_right.x_pos, test_player->bot_right.y_pos);
printf("Jumping Status:         %s\n", test_player->is_jumping == TRUE ? "Jumping" : "Not Jumping");
printf("Vertical Velocity:      %i\n\n", test_player->vert_vel);

}


/* Author : Kevin
*  Purpose: Prints the full location, meaning the x and y position of all vertices of a triangle.
*/
void print_full_triangle_details(Triangle* test_triangle) {
    printf("Top Vertex:       X = %i, Y = %i\n", test_triangle->top.x_pos, test_triangle->top.y_pos);
    printf("Bottom Left:     X = %i, Y = %i\n", test_triangle->bot_left.x_pos, test_triangle->bot_left.y_pos);
    printf("Bottom Right:    X = %i, Y = %i\n", test_triangle->bot_right.x_pos, test_triangle->bot_right.y_pos);
    printf("Horizontal Velocity: %i\n\n", test_triangle->hor_vel);

}


/* Author : Kevin
*  Purpose: Prints the full location, meaning the x and y position of all vertices of a platform.
*/
void print_full_platform_details(Platform* test_platform) {
    printf("Top Left Vertex:               X = %i, Y = %i\n", test_platform->top_left.x_pos, test_platform->top_left.y_pos);
    printf("Top Right Vertex:              X = %i, Y = %i\n", test_platform->top_right.x_pos, test_platform->top_right.y_pos);
    printf("Bottom Left Vertex:            X = %i, Y = %i\n", test_platform->bot_left.x_pos, test_platform->bot_left.y_pos);
    printf("Bottom Right Vertex:           X = %i, Y = %i\n", test_platform->bot_right.x_pos, test_platform->bot_right.y_pos);
    printf("Horizontal Velocity:           %i\n\n", test_platform->hor_vel);
}



/* Author : Kevin
*  Purpose: Prints the y position of the ground (the top edge of the ground).
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
