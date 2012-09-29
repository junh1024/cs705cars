/** Test if a car should be spawned or not every second. k becomes 1 if a car should be spawned otherwise k becomes 0.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
const float max_rand=32767;
int spawnOrNot() {
	float max_car=900; // Density assumed: 900 car per hour
	float probability=max_car/3600; // =1/4 car per second
	float range=probability*1.0; // 0.25
	float randnum= 0.0 + rand() / ( RAND_MAX / ( 1.0 - 0.0 ) + 1 ); // generate random number between 0.0 and 1.0 (uniformly distributed)
	if (randnum <=range ) { // if generated random number is smaller than 0.25 return 1 otherwise 0
		return 1;
	} else {
		return 0;
	}
}
int main(){
	int i,k;
	for(i=0;i<10;i++)
	{
		k=spawnOrNot(); // This method is called every second
		printf("%d \n",k);        
	}
 }
