#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> //allows using bool, true and false

#include "globals.h"
#include "vehiclefollowing.h"

float anumber;

int i=0;

FILE * iFile, * oFile;

int main (int argc, char* argv[])
{
	Lane lane1;//a static lane
	
	Lane *thelane;
	
	thelane=&lane1;//pointer to the current lane
	
	thelane->direction=RIGHT;
	
	
	// printf("%d",alane.direction );

	Car firstcar; //static cars
	Car secondcar;
	
	Car *car1;
	Car *car2;
	
	car1=&firstcar;//pointer to car in front
	car2=&secondcar;//pointer to car that's following
	
	car1->location.x=-5;
	car2->speed=0;
	car2->location.x=-20;
	
	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	i=0;
	float distancetonextcar;
	while ( fscanf(iFile,"%f",&anumber) != EOF )//car1pos
	{
		car1->location.x=anumber;

		switch(thelane->direction)//compute the distance to the next car based on lane direction & appropriate xy coords
		{
			case UP:
				distancetonextcar=fabs(car2->location.y-car1->location.y );
				break;
				
			case DOWN:
				distancetonextcar=fabs(car2->location.y-car1->location.y );
				break;
				
			case LEFT:
				distancetonextcar=fabs(car2->location.x-car1->location.x );
				break;
				
			case RIGHT:
				distancetonextcar=fabs(car2->location.x-car1->location.x );
				break;
		}		

		if(distancetonextcar< 7)//smaller than 7 meters abs distace to car1
		{				
			car2->speed-=DECEL; //slow down
		}
		else
		{
			car2->speed+=ACCEL;//speed up
		}
			
		if(car2->speed<0) //can't have negative speed
		{
			car2->speed=0;
		}
		if (car2->speed>=60)//limit speed to 60kmh
		{
			car2->speed=60;
		}
		
		switch(thelane->direction)//update position of car2 by adding its speed in m/s
		{
			case UP:
				car2->location.y-=(car2->speed/3.6);
				break;
				
			case DOWN:
				car2->location.y+=(car2->speed/3.6);
				break;
				
			case LEFT:
				car2->location.x-=(car2->speed/3.6);
				break;
				
			case RIGHT:
				car2->location.x+=(car2->speed/3.6);
				break;
		}

		fprintf(oFile,"%f\n",car2->location.x);//write pos of car2 to file
	}
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
