#ifndef TST_MODEL_H
#define TST_MODEL_H

#include <stdio.h>
#include "models.h"
#include "events.h"
#include "osbind.h"
#include <unistd.h>


void print_full_triangle_details(Triangle* test_triangle);
void print_full_player_details(Player* test_player);
void print_ground(Ground* test_ground);
void print_full_platform_details(Platform* test_platform);

void test_platform_initializer();
void test_triangle_initializer();
void test_player_initializer();
void wait_for_user();

void tst_triangle_movement();
void tst_player_movement();

#endif