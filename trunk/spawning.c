/** Test if a car should be spawned or not every second. k becomes 1 if a car should be spawned otherwise k becomes 0.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
const double max_rand=32767;
const int NUM_SECONDS = 1; 
int spawnOrNot() {
	double max_car=900; // Density assumed: 900 car per hour
	double probability=max_car/3600; // =1/4 car per second
	double range=probability*1.0; // 0.25
	double randnum= 0.0 + rand() / ( RAND_MAX / ( 1.0 - 0.0 ) + 1 ); // generate random number between 0.0 and 1.0 (uniformly distributed)
	if (randnum <=range ) { // if generated random number is smaller than 0.25 return 1 otherwise 0
		return 1;
	} else {
		return 0;
	}
	
}
int main(){
	int k;
	int i=0;    
	double time_counter = 0;      
	clock_t this_time = clock();     
	clock_t last_time = this_time;        
	while(1)     {	// while loop per second
		this_time = clock();          
		time_counter += (double)(this_time - last_time);          
		last_time = this_time;          
		if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))         {             
			time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);             
			k=spawnOrNot(); // This method is called every second
			printf("%d \n",k);        
		}           
	}     
}