#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> //allows using bool, true and false

// #include "globals.h"

float car1pos=-5;
float car2pos=-20;

int car1speed=0;
int car2speed=0;

//from vehiclefolling
int ACCEL = 5; //km/h/tick
int DECEL = 15; //km/h/tick

//from globals
typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SN = UP,    // South to north
    NS = DOWN,  // North to south
    EW = LEFT,  // East to west
    WE = RIGHT  // West to east
} Direction;
typedef struct Point {
    float x;
    float y;
} Point;
typedef struct Car {
    Point location;
    int speed; //km/h
    char * plate; //This is the cars ID number or licence plate
    bool red; //tells the current car that the light for the intersection that it is approaching is red
    bool orange; //tells the current car that the light for the intersection that it is approaching is orange
    bool invisible; //sets the car to be dimenionless/invisible. This is used instead of the leader car to stop other cars
    // TurnDirection turn_direction;
} Car;
typedef struct CarLane {
    Car cars[800]; //all the cars in any single lane. This is a circular array??
    int start_index;
    int end_index;
    Direction direction;
    int lane_id;
} CarLane;

float anumber;

int i=0;

FILE * iFile, * oFile;

int main (int argc, char* argv[])
{
	CarLane alane;
	alane.direction=RIGHT;
	printf("%d",alane.direction );

	Car firstcar;
	Car secondcar;
	
	Car *car1;
	Car *car2;
	
	car1=&firstcar;
	car2=&secondcar;
	
	car1->location.x=-5;
	car2->location.x=-20;
	
	printf("%f %f",car1->location.x,car2->location.x );
	
	
	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	i=0;
	while ( fscanf(iFile,"%f",&anumber) != EOF )//car1pos
	{
		car1pos=anumber;
		if(fabs(car2pos-car1pos )< 7)//smaller than 7 meters abs distace to car1
		{				
			car2speed=-DECEL; //slow down
		}
		else
		{
			car2speed+=ACCEL;//speed up
		}
			
		if(car2speed<0) //can't have negative speed
		{
			car2speed=0;
		}
		if (car2speed>=60)//over speed limit of 60kmh
		{
			car2speed=60;
		}
		car2pos+=(car2speed/3.6);

		fprintf(oFile,"%f\n",car2pos);
	}
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
