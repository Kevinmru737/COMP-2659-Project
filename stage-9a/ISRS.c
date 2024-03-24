
#include "ISRS.h"
short timer = 0;



void process_vbl_isr() {

    timer++;

    if (timer == 2)
    {
        update_level(&model, &game_state);
        update_game_objects(&model, &fatal_collision);
        fatal_collision = player_fatal_collision(&model, 0);
        render_request = 1;
        timer = 0;
    }
}




Vector install_vector(int num, Vector vector)
{
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);

    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}
