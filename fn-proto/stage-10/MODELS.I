# 1 "models.c" 1
# 1 "./models.h" 1
# 1 "./consts.h" 1





typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef unsigned char bool;
# 5 "./models.h" 2
# 18 "./models.h"
typedef enum {
    OBJECT_RIGHT_OFF_PLAYER,
    OBJECT_NEAR_PLAYER,
    OBJECT_LEFT_OFF_PLAYER,
    PLAYER_STATE_ON_GROUND,
    PLAYER_STATE_MOVING_UP,
    PLAYER_STATE_ON_PLATFORM,
    PLAYER_STATE_MOVING_DOWN
} States;
# 41 "./models.h"
typedef enum {
    PLAYER,
    TRIANGLE,
    PLATFORM_BRICK_1,
    PLATFORM_BRICK_2,
    PLATFORM_1,
    PLATFORM_SHORT
} Game_Object_Type;


typedef struct
{
    int x_pos, y_pos;
}Vertex;
# 74 "./models.h"
typedef struct {
    Vertex top_left, bottom_left, top_right, bottom_right;
    Game_Object_Type type;
    States state;
    short object_velocity;
} Game_Object;
# 87 "./models.h"
typedef struct {
    unsigned int y_pos;
} Ground;
# 98 "./models.h"
typedef struct {
    Game_Object game_objects[20];
    short num_active_objects;
	Ground ground;
} Model;




void initialize_game_object(int x, int y, Game_Object * object, Game_Object_Type type);
void initialize_ground(Ground* ground);
bool player_fatal_collision(Model *model);
bool point_inside_triangle(Vertex* point, Game_Object *triangle);
# 1 "models.c" 2
# 20 "models.c"
void initialize_game_object(int x, int y, Game_Object * object,
                            Game_Object_Type type) {


     object->top_left.x_pos = x;
     object->top_left.y_pos = y;
     object->bottom_right.x_pos = x + 31 ;
     object->bottom_right.y_pos = y + 31 ;


     object->bottom_left.x_pos = x;
	 object->bottom_right.x_pos = x + 31 ;
     object->bottom_left.y_pos = (type == PLATFORM_SHORT) ?
             (y + 15 ) : (y + 31 );
	 object->bottom_right.y_pos = (type == PLATFORM_SHORT) ?
             (y + 15 ) : (y + 31 );



     object->top_right.y_pos = y;
     object->top_right.x_pos = (type == TRIANGLE) ?
             (x + 15 ) : (x + 31 );


     object->object_velocity = (type == PLAYER) ? 0 : 4 ;
     object->type = type;

     if(type == PLAYER) {
         object->state= PLAYER_STATE_ON_GROUND;
     } else {
         object->state = OBJECT_RIGHT_OFF_PLAYER;
     }

}
# 62 "models.c"
void initialize_ground(Ground* ptr_ground) {
	ptr_ground->y_pos = 271 ;
}
# 88 "models.c"
bool player_fatal_collision(Model *model) {
    Game_Object * player = &(model->game_objects[0 ]);
	Game_Object *object;
    short i= 0  + 1;
    bool fatal_collision_detected = 0 ;
    for(i; i< model->num_active_objects; i++) {
		object = &(model->game_objects[i]);


        if (object->state != OBJECT_NEAR_PLAYER ||
            player->top_left.y_pos > object->bottom_left.y_pos ||
            player->bottom_left.y_pos < object->top_left.y_pos)  continue;

		if(object->type == TRIANGLE) {

			 if(point_inside_triangle( &(player->bottom_left), object) ||
               point_inside_triangle( & (player->bottom_right), object) ||
               point_inside_triangle( &(player->top_left), object)   ||
               point_inside_triangle( & (player->top_right), object) ) {
                 fatal_collision_detected = 1 ;
            }
		} else {

            if(player->bottom_left.y_pos > object->top_left.y_pos) {
                fatal_collision_detected = 1 ;
			}
		}

    }

    return fatal_collision_detected;
}
# 144 "models.c"
bool point_inside_triangle(Vertex* point, Game_Object *triangle) {

    int y_on_hypotenuse_from_bot_left, y_on_hypotenuse_from_top;
    int point_x_pos = point->x_pos , point_y_pos = point->y_pos;
    bool is_inside = 0 ;


    if(point_y_pos >= triangle->top_right.y_pos &&
        point_y_pos <= triangle->bottom_left.y_pos) {



        if(point_x_pos >= triangle->bottom_left.x_pos &&
           point_x_pos <= triangle->top_right.x_pos) {
            y_on_hypotenuse_from_bot_left =
            -((point_x_pos - triangle->bottom_left.x_pos) << 2)
             + triangle->bottom_left.y_pos;

            if (y_on_hypotenuse_from_bot_left <= point_y_pos) {
                is_inside = 1 ;
            }
        }


        if(point_x_pos >= triangle->top_right.x_pos  &&
           point_x_pos<= triangle->bottom_right.x_pos) {
            y_on_hypotenuse_from_top =
            ((point_x_pos - triangle->top_right.x_pos) << 2)
            + triangle->top_right.y_pos;

            if (y_on_hypotenuse_from_top <= point_y_pos) {
                is_inside = 1 ;
            }
        }
    }
    return is_inside;
}
