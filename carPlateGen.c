/** Generates car plate number (3 numbers and 3 chars)
*/
// #include <string.h>
#include <stdlib.h>
#include <stdio.h>
// #include <math.h>
// #include <time.h>

//this function generates a gar plate on the given char pointer
void generatecarplate(char* plate) {
	char letters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i,j; //temp variables
	char h;

	for (i=0;i<3;i++) { //generate 3 letters
		j=rand()%25;
		plate[i] = letters[j];
	}
	
	for (i=3;i<6;i++) { //generate 3 numbers
	j=rand()%10;
	h=(char)(((int)'0')+j); 
	plate[i] = h;
	}
	plate[6]='\0'; //null character terminator EOS

	return;
}

int main() {
	int i;
	char theplate[7];
	// srand((unsigned)time(NULL));//enable for seed which is based on time, else will generate same plates each run
	
	for(i=0;i<5;i++) {
		generatecarplate(theplate);
		printf("%s\n",theplate);
	}
	return 0;
}
