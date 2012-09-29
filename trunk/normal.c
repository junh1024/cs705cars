/*
 ============================================================================
 Name        : 705pro.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int deviateAvailable=0;
float storedDeviate;
double polar;
double rsquared;
double var1;
double var2;
double max_rand=32767;

double randn_notrig(double mu, double sigma) {
			//	deviate from previous calculation


	//	If no deviate has been stored, the polar Box-Muller transformation is
	//	performed, producing two independent normally-distributed random
	//	deviates.  One is stored for the next round, and one is returned.
	if (!deviateAvailable) {

		//	choose pairs of uniformly distributed deviates, discarding those
		//	that don't fall within the unit circle
		do {
			int randnum1;
			double randnum2;
			randnum1=rand();
			randnum2=(double)randnum1;
			var1=2.0*( randnum2/max_rand ) - 1.0;
			randnum1=rand();
			randnum2=(double)randnum1;
			var2=2.0*( randnum2/max_rand ) - 1.0;
			rsquared=var1*var1+var2*var2;
		} while ( rsquared>=1.0 || rsquared == 0.0);

		//	calculate polar tranformation for each deviate
		polar=sqrt(-2.0*log(rsquared)/rsquared);

		//	store first deviate and set flag
		storedDeviate=var1*polar;
		deviateAvailable=1;

		//	return second deviate
		return var2*polar*sigma + mu;
	}

	//	If a deviate is available from a previous call to this function, it is
	//	returned, and the flag is set to false.
	else {
		deviateAvailable=0;
		return storedDeviate*sigma + mu;
	}
}

int main(){
	double k;
	int i=0;
	for(;i<10;i++) {
		k=randn_notrig(0.495,0.24);
		printf("%f \n",k);
	}
}
