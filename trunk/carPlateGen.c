/** Generates car plate number (3 numbers and 3 chars)
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

char* generate() {
	char letters[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char plate[6];
	int i;
	int k;
	char h;
	int j;

	for (i=0;i<3;i++) {
		j=rand()%25;
		plate[i] = letters[j];
	}
	
	for (i=0;i<3;i++) {
	k=rand()%10;
	h=(char)(((int)'0')+k); 
	plate[i+3] = h;
	}
	return plate;
}

int main() {
	int i;
	char* k;
	srand((unsigned)time(NULL));
	for(i=0;i<100;i++) {
		k=generate();
		printf("%c%c%c%c%c%c\n",k[0],k[1],k[2],k[3],k[4],k[5]);
	}
}
