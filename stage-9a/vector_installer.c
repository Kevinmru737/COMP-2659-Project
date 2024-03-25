

#include "vector_installer.h"


/*
 * Purpose: Installs a new isr at the specified vector location. Num is the vector number
 *          to replace and vector is the new isr.
 */
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

