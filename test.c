#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> //allows using bool, true and false

#include "globals.h"
#include "vehiclefollowing.h"

float anumber;
float distancetonextcar;

FILE * iFile, * oFile;

int main (int argc, char* argv[])
{
	Lane lane1;//a static lane
	Lane *thelane;
	thelane=&lane1;//pointer to the current lane
	
	thelane->direction=RIGHT;
	Direction current_car_direction = thelane->direction;

	Car firstcar; //static cars
	Car secondcar;
	
	Car *carInFront;
	Car *currentCar;
	
	carInFront=&firstcar;//pointer to car in front
	currentCar=&secondcar;//pointer to car that's following
	
	carInFront->location.x=-5;
	currentCar->speed=0;
	currentCar->location.x=-20;
	
	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	while ( fscanf(iFile,"%f",&anumber) != EOF )//car1pos
	{
		carInFront->location.x=anumber;

		switch(current_car_direction)//compute the distance to the next car based on lane direction & appropriate xy coords
		{
			case UP:
				distancetonextcar=fabs(currentCar->location.y-carInFront->location.y );
				break;
				
			case DOWN:
				distancetonextcar=fabs(currentCar->location.y-carInFront->location.y );
				break;
				
			case LEFT:
				distancetonextcar=fabs(currentCar->location.x-carInFront->location.x );
				break;
				
			case RIGHT:
				distancetonextcar=fabs(currentCar->location.x-carInFront->location.x );
				break;
		}		

		if(distancetonextcar< 7)//smaller than 7 meters abs distace to carInFront
		{
			currentCar->speed-=DECEL; //slow down
		}
		else
		{
			currentCar->speed+=ACCEL;//speed up
		}
			
		if(currentCar->speed<0) //can't have negative speed
		{
			currentCar->speed=0;
		}
		if (currentCar->speed>=global_speed_limit)//speed limit in kmh
		{
			currentCar->speed=global_speed_limit;
		}
		
		switch(current_car_direction)//update position of currentCar by adding its speed in m/s
		{
			case UP:
				currentCar->location.y-=(currentCar->speed/3.6);
				break;
				
			case DOWN:
				currentCar->location.y+=(currentCar->speed/3.6);
				break;
				
			case LEFT:
				currentCar->location.x-=(currentCar->speed/3.6);
				break;
				
			case RIGHT:
				currentCar->location.x+=(currentCar->speed/3.6);
				break;
		}

		fprintf(oFile,"%f\n",currentCar->location.x);//write pos of currentCar to file
	}
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
