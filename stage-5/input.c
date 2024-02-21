#include "input.h"

/* Purpose: changes the  character pointer passed if a valid key was pressed, ie = (ESCAPE OR SPACE)
*/
void user_input(char *inp) {
	char ch;
	
	if (Cconis() ) 
	{
		ch = (char) Cnecin();
		
		if( ch == ' '|| ch == '\033') {
			*inp = ch;
		}
		
	} 

}
