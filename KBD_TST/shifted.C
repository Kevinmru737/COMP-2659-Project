#include <osbind.h>
#include <stdio.h>

int main()
{
char value;
int i = 0;
char *scancode2_asci = (char*) ((Keytbl(-1,-1,-1))->shift);


    FILE *filePointer; 

    filePointer = fopen("shifted.txt", "w");

    if (filePointer == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    fprintf(filePointer, "char shifted[] = {\n");

   for(i; i <= 114; i++) {

	value = scancode2_asci[i];

	fprintf(filePointer,"0x%x, ", value);


}

   

   fprintf(filePointer, "};\n");
   fclose(filePointer);




return 0;



}
