# 1 "models.c" 1
# 1 "./models.h" 1
# 1 "./bool.h" 1



typedef unsigned char bool;
# 4 "./models.h" 2
# 14 "./models.h"
typedef enum {
    OBJECT_RIGHT_OFF_PLAYER,
    OBJECT_NEAR_PLAYER,
    OBJECT_LEFT_OFF_PLAYER,
    PLAYER_STATE_ON_GROUND,
    PLAYER_STATE_MOVING_UP,
    PLAYER_STATE_ON_PLATFORM,
    PLAYER_STATE_MOVING_DOWN
} States;
# 37 "./models.h"
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
# 68 "./models.h"
typedef struct {
    Vertex top_left, bottom_left, top_right, bottom_right;
    Game_Object_Type type;
    States state;
    short object_velocity;
} Game_Object;

typedef struct {
    unsigned int y_pos;
} Ground;


typedef struct {
    Game_Object game_objects[15];
    short num_active_objects;
	Ground ground;
} Model;





void initialize_game_object(int x, int y, Game_Object * object, Game_Object_Type type);
void initialize_ground(Ground* ground);

bool player_fatal_collision(Model *model, short player_num);
bool point_inside_triangle(Vertex* point, Game_Object *triangle);
# 1 "models.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 2 "models.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 3 "models.c" 2
# 20 "models.c"
void initialize_game_object(int x, int y, Game_Object * object, Game_Object_Type type) {


     object->top_left.x_pos = x;
     object->top_left.y_pos = y;
     object->bottom_right.x_pos = x + 31 ;
     object->bottom_right.y_pos = y + 31 ;


     object->bottom_left.x_pos = x;
	 object->bottom_right.x_pos = x + 31 ;
     object->bottom_left.y_pos = (type == PLATFORM_SHORT) ? (y + 15 ) : (y + 31 );
	 object->bottom_right.y_pos =(type == PLATFORM_SHORT) ? (y + 15 ) : (y + 31 );




     object->top_right.y_pos = y;
     object->top_right.x_pos = (type == TRIANGLE) ? (x + 15 ) : (x + 31 );

     object->object_velocity = (type == PLAYER) ? 0 : 4 ;

     object->type = type;

     if(type == PLAYER) {
         object->state= PLAYER_STATE_ON_GROUND;
     } else {
         object->state = OBJECT_RIGHT_OFF_PLAYER;

     }

}
# 65 "models.c"
void initialize_ground(Ground* ptr_ground) {
	ptr_ground->y_pos = 271 ;
}
# 89 "models.c"
bool player_fatal_collision(Model *model, short player_num) {
    Game_Object * player = &(model->game_objects[player_num]);
	Game_Object *object;
    short i= 1;

    for(i; i< model->num_active_objects; i++) {
		object = &(model->game_objects[i]);



        if (object->state != OBJECT_NEAR_PLAYER || player->top_left.y_pos > object->bottom_left.y_pos
			|| player->bottom_left.y_pos < object->top_left.y_pos)  continue;


		if(object->type == TRIANGLE) {

			 if(point_inside_triangle( &(player->bottom_left), object)   ||
               point_inside_triangle( & (player->bottom_right), object) ||
               point_inside_triangle( &(player->top_left), object)   ||
               point_inside_triangle( & (player->top_right), object)  ) {
                return 1 ;
            }

		} else {

			if(player->bottom_left.y_pos > object->top_left.y_pos) {
					return 1 ;
			}



		}

    }

    return 0 ;
}
# 149 "models.c"
bool point_inside_triangle(Vertex* point, Game_Object *triangle) {

    int y_on_hypotenuse_from_bot_left, y_on_hypotenuse_from_top;
    int point_x_pos = point->x_pos , point_y_pos = point->y_pos  ;

    if(point_y_pos < triangle->top_right.y_pos || point_y_pos > triangle->bottom_left.y_pos) {
            return 0 ;
    }


    if(point_x_pos >= triangle->bottom_left.x_pos && point_x_pos <= triangle->top_right.x_pos) {
        y_on_hypotenuse_from_bot_left = -((point_x_pos - triangle->bottom_left.x_pos) << 2) + triangle->bottom_left.y_pos;
        if (y_on_hypotenuse_from_bot_left <= point_y_pos) {
            return 1 ;
        }
    }


    if(point_x_pos >= triangle->top_right.x_pos  && point_x_pos<= triangle->bottom_right.x_pos) {

        y_on_hypotenuse_from_top = ((point_x_pos - triangle->top_right.x_pos) << 2) + triangle->top_right.y_pos;
        if (y_on_hypotenuse_from_top <= point_y_pos) {
            return 1 ;
        }
    }

    return 0 ;

}
