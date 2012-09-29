/** Generates car plate number (3 numbers and 3 chars)
*/
#include <string.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

char* generatecarplate() {
	char letters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char plate[7];
	int i;
	int k;
	char h;
	int j;

	for (i=0;i<3;i++) {
		j=rand()%25;
		plate[i] = letters[j];
	}
	
	for (i=3;i<6;i++) {
	k=rand()%10;
	h=(char)(((int)'0')+k); 
	plate[i] = h;
	}
	plate[6]='\0';
	
	char *theplate;
	theplate = (char *)malloc(7*sizeof(char));
	strcpy(theplate,plate);
	
	return theplate;
}

int main() {
	int i;
	char k[7];
	// srand((unsigned)time(NULL));
	
	for(i=0;i<5;i++) {
		strcpy(k,generatecarplate());
		printf("%s\n",k);
		// printf("%d\n",k);
	}
}
