#include "input.h"

/* Purpose: changes the  character pointer passed if a valid key was pressed, ie = (ESCAPE OR SPACE)
*/
/*********************************************************
 *  Purpose: Changes the  character pointer passed if a valid key was pressed, ie = (ESCAPE OR SPACE)
 *
 * Details: This function checks for user input and captures specific characters
 *         (space ' ' or escape '\033'). If one of these specific characters is
 *        detected, it is stored in the location pointed to by the input parameter.
 *
 * Input: Pointer to a character variable where the detected character
 *        will be stored if it matches the specified conditions.
 * Output: The function modifies the value pointed to by the input parameter
 *         only if a space or escape character is detected. Otherwise,not.
 *
 *********************************************************/
void user_input(char *inp) {
    char ch;
    
    if (is_buffer_empty() == FALSE) {
        ch = (char) get_value_from_buffer();
        
        if (ch == ' ' || ch == '\033') {
            *inp = ch;
        }
    }
}