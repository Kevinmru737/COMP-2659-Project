 /* Overview:
 *          This is test driver to the various functions in the Raster Library.
 *          It stores each function's results in a their own results file. 
 *          This uses the test bitmaps in tst_dat.c to as globals to for expected
 *          input and outputs
 Last modifed by Depanshu on 1 Feb 2024
*/

#include "osbind.h"
#include <stdio.h>
#include <stdlib.h>
#include "tst_dat.h"
#include "RASTER.H"

typedef int bool;

#define FALSE 0
#define TRUE 1

void test_32_bit_drawer();
void test_draw_32_bitmap(FILE *file, UINT32* input_bitmap, UINT32* expected_bitmap, 
                         int width, int height, int x , int y, bool start_pixel_not_alligned, int test_num);


void test_draw_16_bitmap(FILE *file, UINT16* input_bitmap, UINT16* expected_bitmap,
                        int width, int height, int x , int y, bool start_pixel_not_alligned, int test_num);
void test_16_bit_drawer();

void test_draw_8_bitmap(FILE *file, UINT8* input_bitmap, UINT8* expected_bitmap,
                        int width, int height, int x , int y, bool start_pixel_not_alligned, int test_num);
void test_8_bit_drawer();
void wait_for_user();
void test_32_bit_clear_func();
void test_16_bit_clear_func();



int main()
{
  
    UINT16* base = Physbase();
    int x = 0;
   
    printf("Raster Library Test Program\n");
    printf("Each function of the Raster Library will generate results saved in seperate files file.\n");
    printf("Press any key to proceed with the tests...\n");
    wait_for_user();

    test_32_bit_drawer();
    test_16_bit_drawer();
    test_8_bit_drawer();
    test_32_bit_clear_func();
    test_16_bit_clear_func();

    return 0;

 }





/*
* Author: Depanshu 
* Purpose: Test drawing function for bitmaps with 32-bit values.
*
* Parameters:
*   None. Utilizes global variables for input and expected output bitmaps,
*   located in the maps_tst.c file
*
* Details:
*   This function iterates through a set of test cases to validate the functionality
*   of the `draw_32_bit_bitmap` function. It performs tests by comparing the
*   output of the drawing function ( frame buffer values) against expected bitmap 
*   Results of each test are written to a file named "32_bit_result.txt" 
*
*Test Cases: 
*       	1: Verify drawing of a bitmap with the smallest width (32 pixels)
*           2:Validate drawing of a bitmap with the longest width (640 pixels) and at a different height	
*           3:Ensure correct drawing of a bitmap at an unaligned column	
*           5:Validates drawing of a bitmap with a minimum height of 1
*/
void test_32_bit_drawer() {

    FILE* file;
    char (*test_cases_32_bit_drawer)[100] = TEST_CASES_FOR_32_BIT_DRAWER; /*test case descriptions */
    UINT32* base = Physbase();

    /* pointer to array of pointer with the input bitmaps */
    UINT32 ** input_bitmaps = test_32_bit_drawer_input_buffers; 
    
    /* array of pointers with the expected bitmaps */
    UINT32 ** expected_bitmaps = test_32_bit_drawer_expected_buffers;


    file = fopen("32_bit_plotter_results.txt", "w");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    printf("TESTING draw_32_bit_bitmap function\n");
    printf("Results will be stored in 32_bit_plotter_results.txt\n");
   
    /*---------------------------------------CASE 1------------------------------------------*/

    fprintf(file, "%s", *test_cases_32_bit_drawer++);
    wait_for_user();
    clear_screen(base);
    test_draw_32_bitmap(file, (*input_bitmaps++), (*expected_bitmaps++), 32, 32, 0 , 0, FALSE, 1);



    /*---------------------------------------CASE 2------------------------------------------*/

    fprintf(file, "%s", *test_cases_32_bit_drawer++);
    wait_for_user();
    clear_screen(base);
    test_draw_32_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 640, 5, 0 , 10, FALSE, 2);



    /*---------------------------------------CASE 3------------------------------------------*/

    fprintf(file, "%s", *test_cases_32_bit_drawer++);
    wait_for_user();
    clear_screen(base);
    test_draw_32_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 32, 7, 59 , 10, TRUE, 3);



    /*---------------------------------------CASE 4------------------------------------------*/

    fprintf(file, "%s", *test_cases_32_bit_drawer++);
    wait_for_user();
    clear_screen(base);
    test_draw_32_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 32, 1, 64 , 22, FALSE, 4);

    fclose(file);


}

/* Author: Depanshu
*  Purpose: Helper function for testing the drawing function for bitmaps with 32-bit values.
*
* Details: Executes a drawing test by drawing the  `input_bitmap` on the screen and
*          comparing the frame buffer with `expected_bitmap`. The values are logged to a file.
*
*/
void test_draw_32_bitmap(FILE *file, UINT32* input_bitmap, UINT32* expected_bitmap,int width, int height, int x , int y, bool start_pixel_not_alligned, int test_num){

    int test_passed = TRUE;
    int UINT32_per_row = width >> 5; /*number of long covered by the bitmap being tested */
    int col;
    UINT32* base = Physbase();

    /*Draw the input base map */
    draw_32_bit_bitmap(base, x, y, height, width, input_bitmap);
    base += OFFSET_TO_UINT32(x,y);

    /*The bitmap covers one more long if the starting pixel is not 32 bit aligned*/
    if(start_pixel_not_alligned == TRUE) {
        UINT32_per_row++;
	}

    /* Loop through each row */
    for (height; height > 0; height--) {

        for (col = UINT32_per_row; col > 0; col--) {
            if (*base != *expected_bitmap) {
                test_passed = FALSE;
            }
            fprintf(file, "Expected Value: %lX. Actual Value: %lX.\n", *expected_bitmap++, *base++);
        }

        base +=(UINT32_PER_SCANLINE - UINT32_per_row);
        }


    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", test_num) : fprintf(file, "\nTEST %d FAILED \n\n", test_num);

}




/*
* Author: Depanshu Suyal
* Purpose: Test drawing function for bitmaps with 16-bit values.
*
* Parameters:
*   None. Utilizes global variables for input and expected output bitmaps,
*   located in the maps_tst.c file
*
* Details:
*   This function iterates through a set of test cases to validate the functionality
*   of the `draw_16_bit_bitmap` function. It performs tests by comparing the
*   output of the drawing function ( frame buffer values) against expected bitmap 
*   Results of each test are written to a file named "16_bit_result.txt" 
*
*Test Cases: 
*       	1: Verify drawing of a bitmap with the smallest width (16 pixels)
*           2:Validate drawing of a bitmap with the longest width (640 pixels) and at a different height	
*           3:Ensure correct drawing of a bitmap at an unaligned column	
*           4:Validates drawing of a bitmap with a minimum height of 1
*/

void test_16_bit_drawer() {

    FILE* file;
    char (*test_cases_16_bit_drawer)[100] = TEST_CASES_FOR_16_BIT_DRAWER; /*test case descriptions */
    UINT16* base = Physbase();

    /* pointer to array of pointer with the input bitmaps */
    UINT16 ** input_bitmaps = test_16_bit_drawer_input_buffers; 
    
    /* array of pointers with the expected bitmaps */
    UINT16 ** expected_bitmaps = test_16_bit_drawer_expected_buffers;


    file = fopen("16_bit_plotter_results.txt", "w");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    printf("TESTING draw_16_bit_bitmap function\n");
    printf("Results will be stored in 16_bit_plotter_results.txt\n");
   
    /*---------------------------------------CASE 1------------------------------------------*/
    
    fprintf(file, "%s", *test_cases_16_bit_drawer++);
    test_draw_16_bitmap(file, (*input_bitmaps++), (*expected_bitmaps++), 16, 16, 0 , 0, FALSE, 1);

    /*---------------------------------------CASE 2------------------------------------------*/
    fprintf(file, "%s", *test_cases_16_bit_drawer++);
    test_draw_16_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 640, 2, 0 , 10, FALSE, 2);

    /*---------------------------------------CASE 3-------------------------------------------*/

    fprintf(file, "%s", *test_cases_16_bit_drawer++);
    test_draw_16_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 16, 5, 19 , 10, TRUE, 3);


    /*---------------------------------------CASE 4-------------------------------------------*/

    fprintf(file, "%s", *test_cases_16_bit_drawer++);

    test_draw_16_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 640, 1, 0 , 300, FALSE, 4);
    
    fclose(file);


}


/* Author: Depanshu
*  Purpose: Helper function for testing the drawing function for bitmaps with 16-bit values.
*
* Details: Executes a drawing test by drawing the  `input_bitmap` on the screen and
*          comparing the frame buffer with `expected_bitmap`. The values are logged to a file.
*
*/
void test_draw_16_bitmap(FILE *file, UINT16* input_bitmap, UINT16* expected_bitmap,int width, int height, int x , int y, bool start_pixel_not_alligned, int test_num){

    int test_passed = TRUE;
    int UINT16_per_row = width >> 4; /*number of word covered by the bitmap being tested */
    int col;
    UINT16* base = Physbase();
    
    wait_for_user();
    clear_screen((UINT32*) base);

    /*Draw the input base map */
    draw_16_bit_bitmap(base, x, y, height, width, input_bitmap);
    base += OFFSET_TO_UINT16(x,y);

    /*The bitmap covers one more long if the starting pixel is not 32 bit aligned*/
    if(start_pixel_not_alligned == TRUE) {
        UINT16_per_row++;
	}

    /* Loop through each row */
    for (height; height > 0; height--) {

        for (col = UINT16_per_row; col > 0; col--) {
            if (*base != *expected_bitmap) {
                test_passed = FALSE;
            }
            fprintf(file, "Expected Value: %04X. Actual Value: %04X.\n", *expected_bitmap++, *base++);
        }

        base +=(UINT16_PER_SCANLINE - UINT16_per_row);

        }


    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", test_num) : fprintf(file, "\nTEST %d FAILED \n\n", test_num);

}






/*
* Author: Depanshu Suyal
* Purpose: Test drawing function for bitmaps with 8-bit values.
*
* Parameters:
*   None. Utilizes global variables for input and expected output bitmaps,
*   located in the maps_tst.c file
*
* Details:
*   This function iterates through a set of test cases to validate the functionality
*   of the `draw_8_bit_bitmap` function. It performs tests by comparing the
*   output of the drawing function ( frame buffer values) against expected bitmap 
*   Results of each test are written to a file named "8_bit_result.txt" 
*
*Test Cases: 
*       	1: Verify drawing of a bitmap with the smallest width (8 pixels)
*           2:Validate drawing of a bitmap with the longest width (640 pixels) and at a different height	
*           3:Ensure correct drawing of a bitmap at an unaligned column	
*           4:Validates drawing of a bitmap with a minimum height of 1
*/
void test_8_bit_drawer(){
   FILE* file;
    char (*test_cases_8_bit_drawer)[100] = TEST_CASES_FOR_8_BIT_DRAWER; /*test case descriptions */
    UINT8* base = Physbase();

    /* pointer to array of pointer with the input bitmaps */
    UINT8 ** input_bitmaps = test_8_bit_drawer_input_buffers; 
    
    /* array of pointers with the expected bitmaps */
    UINT8 ** expected_bitmaps = test_8_bit_drawer_expected_buffers;


    file = fopen("8_bit_plotter_results.txt", "w");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    printf("TESTING draw_8_bit_bitmap function\n");
    printf("Results will be stored in 8_bit_plotter_results.txt\n");
   
    /*---------------------------------------CASE 1------------------------------------------*/
    
    fprintf(file, "%s", *test_cases_8_bit_drawer++);
    
    test_draw_8_bitmap(file, (*input_bitmaps++), (*expected_bitmaps++), 8, 8, 16 , 250, FALSE, 1);

    /*---------------------------------------CASE 2------------------------------------------*/
    fprintf(file, "%s", *test_cases_8_bit_drawer++);
    test_draw_8_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 640, 2, 0 , 10, FALSE, 2);

    /*---------------------------------------CASE 3-------------------------------------------*/

    fprintf(file, "%s", *test_cases_8_bit_drawer++);
    test_draw_8_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 8, 8, 27 , 27, TRUE, 3);


    /*---------------------------------------CASE 4-------------------------------------------*/

    fprintf(file, "%s", *test_cases_8_bit_drawer++);

    test_draw_8_bitmap(file,(*input_bitmaps++), (*expected_bitmaps++), 640, 1,0 , 300, FALSE, 4);
    
    fclose(file);


}



/* Author: Depanshu
*  Purpose: Helper function for testing the drawing function for bitmaps with 8-bit values.
*
* Details: Executes a drawing test by drawing the  `input_bitmap` on the screen and
*          comparing the frame buffer with `expected_bitmap`. The values are logged to a file.
*
*/

void test_draw_8_bitmap(FILE *file, UINT8* input_bitmap, UINT8* expected_bitmap,int width, int height,
                        int x , int y, bool start_pixel_not_alligned, int test_num) {

    int test_passed = TRUE;
    int UINT8_per_row = width >> 3; /*number of bytes covered by the bitmap being tested */
    int col;
    UINT8* base = Physbase();
    
    wait_for_user();
    clear_screen((UINT32*) base);

   /* Draw the input base map */
    draw_8_bit_bitmap(base, x, y, height, width, input_bitmap);
    base += OFFSET_TO_UINT8(x,y);

    /*The bitmap covers one more byte if the starting pixel is not 8 bit aligned*/
    if(start_pixel_not_alligned == TRUE) {
        UINT8_per_row++;
	}

    /* Loop through each row */
    for (height; height > 0; height--) {

        for (col = UINT8_per_row; col > 0; col--) {
            if (*base != *expected_bitmap) {
                test_passed = FALSE;
            }
            fprintf(file, "Expected Value: %02X. Actual Value: %02X.\n", *expected_bitmap++, *base++);
        }

        base +=(UINT8_PER_SCANLINE - UINT8_per_row);

        }


    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", test_num) : fprintf(file, "\nTEST %d FAILED \n\n", test_num);



}


/*
*
* Purpose: Test the function which clears a drawn 32 bit bitmap from the frame buffer ( clear_32_bit_bitmap);
*
* Parameters:
*   None
*
*Test Cases: 
*       	1: Clears frame buffer at a aligned starting bit( ie 32)
*           2: Clears frame buffer at an unalligned starting bit( ie 43)
*           3: Clears the bitmap with the height of 1
*
* Uses the test arrays declare in test_dat.c for the test cases
*/
void test_32_bit_clear_func() {
    FILE* file;
    int i = 0;
    bool test_passed = TRUE;
    UINT32* base = Physbase();


    file = fopen("clr_32_bit.txt", "w");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    printf("TESTING clear_32_bit_bitmap) function\n");
    printf("Results will be stored in clr_32_bit.txt\n");
   


    /*---------------------------------------CASE 1------------------------------------------*/


    fprintf(file, "%s", "Case 1: Clears frame buffer at a aligned starting bit( ie 32) \n");
    wait_for_user();
    clear_screen(base);


    draw_32_bit_bitmap(base, 32, 32, 32, 32, cube_32_x_32);
    Vsync();
    clear_32_bit_bitmap(base, 32,32,32,32);


    base += OFFSET_TO_UINT32(32,32);
    
    for( i = 0; i < 32; i++) {

        if (*base != 0) {
                test_passed = FALSE;
        }

        fprintf(file, "Expected Value: %08X. Actual Value: %08X.\n", 0, *base);
        base += (UINT32_PER_SCANLINE);
     }

    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", 1) : fprintf(file, "\nTEST %d FAILED \n\n", 1);



    /*---------------------------------------CASE 2------------------------------------------*/
    
    test_passed = TRUE;
    base = Physbase();
    fprintf(file, "%s", "Case 2: Clears frame buffer at an unalligned starting bit( ie 43)");
    wait_for_user();
    clear_screen(base);


    draw_32_bit_bitmap(base, 43, 32, 32, 32, cube_32_x_32);
    Vsync();
    clear_32_bit_bitmap(base, 43,32,32,32);


    base += OFFSET_TO_UINT32(43,32);


    /*Check two longs since drawing at unaligned positons takes the size of the bitmap(1 long in this case) plus one more long*/
    for( i = 0; i < 32; i++) {
        
        if (*base != 0) {
                test_passed = FALSE;
        }
        fprintf(file, "Expected Value: %08X. Actual Value: %08X.\n", 0, *base++);


        if (*base != 0) {
                test_passed = FALSE;
        }
        fprintf(file, "Expected Value: %08X. Actual Value: %08X.\n", 0, *base);

        base += (UINT32_PER_SCANLINE - 1);


     }

    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", 2) : fprintf(file, "\nTEST %d FAILED \n\n", 2);


    /*---------------------------------------CASE 3------------------------------------------*/
    
    test_passed = TRUE;
    base = Physbase();
    fprintf(file, "%s", "Case 3: Clears the bitmap with the height of 1");
    wait_for_user();
    clear_screen(base);


    draw_32_bit_bitmap(base, 0, 32, 1, 640, ground_640_x_128);
    Vsync();
    clear_32_bit_bitmap(base, 0, 32, 1, 640);


    base += OFFSET_TO_UINT32(0,32);

    for( i = 0; i < 20; i++) {
        
        if (*base != 0) {
                test_passed = FALSE;
        }
        fprintf(file, "Expected Value: %08X. Actual Value: %08X.\n", 0, *base++);

     }

    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", 3) : fprintf(file, "\nTEST %d FAILED \n\n", 3);

    fclose(file);

}


/*
* Purpose: Test the function which clears a drawn 16 bit bitmap from the frame buffer ( clear_16_bit_bitmap)
*
* Parameters:
*   None
*
*Test Cases: 
*       	1: Clears frame buffer at a aligned starting bit( ie 16)
*           2: Clears frame buffer at an unalligned starting bit( ie 53)
*           3: Clears the bitmap with the height of 1
*
* Uses the test arrays declare in test_dat.c for the test cases
*/

void test_16_bit_clear_func() {

  FILE* file;
    int i = 0;
    bool test_passed = TRUE;
    UINT16* base = Physbase();

    file = fopen("clr_16_bit.txt", "w");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    printf("TESTING clear_16_bit_bitmap) function\n");
    printf("Results will be stored in clr_16_bit.txt\n");
   


    /*---------------------------------------CASE 1------------------------------------------*/


    fprintf(file, "%s", "Case 1: Clears frame buffer at a aligned starting bit( ie 16) \n");
    wait_for_user();
    clear_screen((UINT32*) base);


    draw_16_bit_bitmap(base, 16, 32, 16, 16, invader_16_x_16);
    Vsync();
    clear_16_bit_bitmap(base, 16, 32, 16, 16);


    base += OFFSET_TO_UINT16(32,32);
    
    for( i = 0; i < 16; i++) {

        if (*base != 0) {
                test_passed = FALSE;
        }

        fprintf(file, "Expected Value: %04X. Actual Value: %04X.\n", 0, *base);
        base += (UINT16_PER_SCANLINE);
     }

    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", 1) : fprintf(file, "\nTEST %d FAILED \n\n", 1);



    /*---------------------------------------CASE 2------------------------------------------*/

    test_passed = TRUE;
    base = Physbase();
    fprintf(file, "%s", "Case 2: Clears frame buffer at an unalligned starting bit( ie 53)");
    wait_for_user();
    clear_screen((UINT32*) base);


    draw_16_bit_bitmap(base, 53, 32, 16, 16, invader_16_x_16);
    Vsync();
    clear_16_bit_bitmap(base, 53, 32, 16, 16);


    base += OFFSET_TO_UINT16(53,32);


    /*Check two words since drawing at unaligned positons takes the size of the bitmap(1 word in this case) plus one more word*/
    for( i = 0; i < 16; i++) {
        
        if (*base != 0) {
                test_passed = FALSE;
        }
        fprintf(file, "Expected Value: %04X. Actual Value: %04X.\n", 0, *base++);


        if (*base != 0) {
                test_passed = FALSE;
        }
        fprintf(file, "Expected Value: %04X. Actual Value: %04X.\n", 0, *base);

        base += (UINT16_PER_SCANLINE - 1);

     }

    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", 2) : fprintf(file, "\nTEST %d FAILED \n\n", 2);


    /*---------------------------------------CASE 3------------------------------------------*/

    test_passed = TRUE;
    base = Physbase();
    fprintf(file, "%s", "Case 3: Clears the bitmap with the height of 1");
    wait_for_user();
    clear_screen((UINT32*) base);


    draw_16_bit_bitmap(base, 53, 32, 1, 16, invader_16_x_16);
    Vsync();
    clear_16_bit_bitmap(base, 53, 32, 1, 16);


    base += OFFSET_TO_UINT16(53,32);

    if (*base != 0) {
            test_passed = FALSE;
    }
    fprintf(file, "Expected Value: %04X. Actual Value: %04X.\n", 0, *base++);

    test_passed == TRUE ? fprintf(file, "\nTEST %d PASSED \n\n", 3) : fprintf(file, "\nTEST %d FAILED \n\n", 3);

    fclose(file);

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






































