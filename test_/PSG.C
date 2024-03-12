#include <osbind.h>
#include <stdio.h>
#define D6_FLAT_FINE 0x5f
#define D6_FLAT_COARSE 0x0 

#define A5_SHARP_FINE 0x78
#define A5_SHARP_COARSE 0x0


#define G6_FLAT_FINE 0x47
#define G6__FLAT_COARSE 0x0

#define F6_FLAT_FINE 0x50
#define F6__FLAT_COARSE 0x0


#define D6_SHARP_FINE 0x5a
#define D6_SHARP_COARSE 0x0

#define A5_SHARP_FINE 0x78
#define A5_SHARP_COARSE 0x0

#define C6_FLAT_FINE  0x6b
#define C6_FLAT_COARSE 0x0

#define G3_FLAT_FINE 0x3b
#define G3_FLAT_COARSE 0x2

#define D3_FLAT_FINE 0xFa
#define D3_FLAT_COARSE 0x2

#define G2_FLAT_FINE 0x75
#define G2_FLAT_COARSE 0x4


#define D3_SHARP_FINE 0xcf
#define D3_SHARP_COARSE 0x2

#define A2_SHARP_FINE 0xc0
#define A2_SHARP_COARSE 0x3

#define F3_FLAT_FINE 0x81
#define F3_FLAT_COARSE 0x2

#define F2_FLAT_FINE 0x01
#define F2_FLAT_COARSE 0x5

#define C3_FLAT_FINE 0x57
#define C3_FLAT_COARSE 0x3

typedef unsigned long UINT32;
UINT32 get_time();


int main()
{

	UINT32 time_now,time_then,time_elapsed;
	volatile unsigned char *PSG_reg_select = 0xFF8800;
	volatile unsigned char *PSG_reg_write  = 0xFF8802;

	
	long old_ssp = Super(0);


      
          *PSG_reg_select = 13;
        *PSG_reg_write  = 0x8;
        *PSG_reg_select = 11;
        *PSG_reg_write  = 0xff;
         *PSG_reg_select = 12;
        *PSG_reg_write  = 0x3;

    
	while (!Cconis()) {

        *PSG_reg_select = 0;
        *PSG_reg_write  = D6_FLAT_FINE;
        *PSG_reg_select = 1;
        *PSG_reg_write  = D6_FLAT_COARSE;
    

        *PSG_reg_select = 2;
        *PSG_reg_write  = G3_FLAT_FINE;
        *PSG_reg_select = 3;
        *PSG_reg_write  = G3_FLAT_COARSE;


        *PSG_reg_select = 4;
        *PSG_reg_write  = D3_FLAT_FINE;
        *PSG_reg_select = 5;
        *PSG_reg_write  = D3_FLAT_COARSE;



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
        *PSG_reg_write  = G2_FLAT_FINE;
        *PSG_reg_select = 3;
        *PSG_reg_write  = G2_FLAT_COARSE;


        *PSG_reg_select = 9;
        *PSG_reg_write  = 0x1f;

        time_then = get_time();
        while(get_time() - time_then < 30) {}

        *PSG_reg_select = 8;
        *PSG_reg_write  = 0;
        *PSG_reg_select = 9;
        *PSG_reg_write  = 0;


        *PSG_reg_select = 0;
        *PSG_reg_write  = A5_SHARP_FINE;
        *PSG_reg_select = 1;
        *PSG_reg_write  = A5_SHARP_COARSE;


        *PSG_reg_select = 2;
        *PSG_reg_write  = G3_FLAT_FINE;
        *PSG_reg_select = 3;
        *PSG_reg_write  = G3_FLAT_COARSE;




        *PSG_reg_select = 4;
        *PSG_reg_write  = D3_FLAT_FINE;
        *PSG_reg_select = 5;
        *PSG_reg_write  = D3_FLAT_COARSE;


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
        *PSG_reg_write  = G2_FLAT_FINE;
        *PSG_reg_select = 3;
        *PSG_reg_write  = G2_FLAT_COARSE;

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


	Cnecin();
	Super(old_ssp);
	return 0;
}
UINT32 get_time(){
	UINT32 time_now;
	UINT32 *timer = (UINT32 *)0x462; /*address of a long word that is auto incremented 70 times per second */
	
	time_now = *timer;
	
	return time_now;
	
}