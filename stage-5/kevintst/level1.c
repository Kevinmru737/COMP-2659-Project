#include "level1.h"
#define SPEED_1 8



void load_level1 (Level level [])
{
    level[0].time = 1;
    initialize_triangle(608, 271 - 31, SPEED_1, &(level[0].triangle));
    level[0].draw_triangle = TRUE;
    level[0].draw_platform = FALSE;


    level[1].time = 3;
    initialize_triangle(608, 240, SPEED_1, &(level[1].triangle));
    initialize_platform(640-64 , 271 - 32, 64, 32, SPEED_1, &(level[1].platform));
    level[1].draw_triangle = FALSE;
    level[1].draw_platform = TRUE;

    level[2].time = 4;
    initialize_triangle(608, 240, SPEED_1, &(level[2].triangle));
    level[2].draw_triangle = TRUE;
    level[2].draw_platform = FALSE;

    level[3].time = 6;
    initialize_platform(640-64 , 271 - 64, 64, 32, SPEED_1, &(level[3].platform));
    level[3].draw_triangle = FALSE;
    level[3].draw_platform = TRUE;





}

/*level1_triangles[0].time = 1;
initialize_triangle(640-32, 271 - 31, 8, level1_triangles[0].triangle);
initialize_platform(640-64 , 271 - 64, 64, 32, 5, level1_triangles[0].platform);
*/
/*
const Level timing_of_platforms [] = 
{
    11, 13



};*/