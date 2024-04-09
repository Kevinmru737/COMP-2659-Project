#include "vct_inst.h"


/*
* Purpose: From one of the labs. Replaces an ISR and returns
*          the original ISR address
*/
Vector install_vector(int num, Vector vector)
{
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    enter_super();

    orig = *vectp;
    *vectp = vector;
    exit_super();
    
    return orig;
}
