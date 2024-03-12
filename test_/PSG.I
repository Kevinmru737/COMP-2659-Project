# 1 "psg.c" 1
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
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
# 1 "psg.c" 2
# 1 "C:/c68/include/stdio.h" 1
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
# 2 "psg.c" 2
# 51 "psg.c"
typedef unsigned long UINT32;
UINT32 get_time();


int main()
{

	UINT32 time_now,time_then,time_elapsed;
	volatile unsigned char *PSG_reg_select = 0xFF8800;
	volatile unsigned char *PSG_reg_write  = 0xFF8802;


	long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;



          *PSG_reg_select = 13;
        *PSG_reg_write  = 0x8;
        *PSG_reg_select = 11;
        *PSG_reg_write  = 0xff;
         *PSG_reg_select = 12;
        *PSG_reg_write  = 0x3;


	while (!(short)_trap_1_w((short)0x0B) ) {

        *PSG_reg_select = 0;
        *PSG_reg_write  = 0x5f ;
        *PSG_reg_select = 1;
        *PSG_reg_write  = 0x0 ;


        *PSG_reg_select = 2;
        *PSG_reg_write  = 0x3b ;
        *PSG_reg_select = 3;
        *PSG_reg_write  = 0x2 ;


        *PSG_reg_select = 4;
        *PSG_reg_write  = 0xFa ;
        *PSG_reg_select = 5;
        *PSG_reg_write  = 0x2 ;



        *PSG_reg_select = 7;
        *PSG_reg_write  = 0x38;



        *PSG_reg_select = 8;
        *PSG_reg_write  = 0x1f;
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0x1f;
        *PSG_reg_select = 10;
        *PSG_reg_write  = 0x1f;


		time_then = get_time();
		while(get_time() - time_then < 30) {}
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0;
        *PSG_reg_select = 10;
        *PSG_reg_write  = 0;

        *PSG_reg_select = 2;
        *PSG_reg_write  = 0x75 ;
        *PSG_reg_select = 3;
        *PSG_reg_write  = 0x4 ;


        *PSG_reg_select = 9;
        *PSG_reg_write  = 0x1f;

        time_then = get_time();
        while(get_time() - time_then < 30) {}

        *PSG_reg_select = 8;
        *PSG_reg_write  = 0;
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0;


        *PSG_reg_select = 0;
        *PSG_reg_write  = 0x78 ;
        *PSG_reg_select = 1;
        *PSG_reg_write  = 0x0 ;


        *PSG_reg_select = 2;
        *PSG_reg_write  = 0x3b ;
        *PSG_reg_select = 3;
        *PSG_reg_write  = 0x2 ;




        *PSG_reg_select = 4;
        *PSG_reg_write  = 0xFa ;
        *PSG_reg_select = 5;
        *PSG_reg_write  = 0x2 ;


        *PSG_reg_select = 8;
        *PSG_reg_write  = 0x1f;
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0x1f;
        *PSG_reg_select = 10;
        *PSG_reg_write  = 0x1f;
        time_then = get_time();

        while(get_time() - time_then < 30) {}
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0;
        *PSG_reg_select = 10;
        *PSG_reg_write  = 0;

        *PSG_reg_select = 2;
        *PSG_reg_write  = 0x75 ;
        *PSG_reg_select = 3;
        *PSG_reg_write  = 0x4 ;

        *PSG_reg_select = 9;
        *PSG_reg_write  = 0x1f;
        time_then = get_time();

        while(get_time() - time_then < 30) {}

        *PSG_reg_select = 8;
        *PSG_reg_write  = 0;
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0;
        *PSG_reg_select = 10;
        *PSG_reg_write  = 0;
    }


	*PSG_reg_select = 8;
	*PSG_reg_write  = 0;
	*PSG_reg_select = 9;
	*PSG_reg_write  = 0;
    *PSG_reg_select = 10;
    *PSG_reg_write  = 0;


	_trap_1_w((short)0x08) ;
	_trap_1_wl((short)0x20,(long)(old_ssp)) ;
	return 0;
}
UINT32 get_time(){
	UINT32 time_now;
	UINT32 *timer = (UINT32 *)0x462;

	time_now = *timer;

	return time_now;

}
