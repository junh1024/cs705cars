#ifndef VTL_GLOBALS_H
#define VTL_GLOBALS_H

#include <stdio.h>
#include <stdlib.h>

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

/**
 * This structure represents a single car in the simulation
 * Each car has its own signals for red and orange internally.
 * VTL group will turn red or orange on as appropriate in the leader car??
 * Orange is currently unused but may be used later.
 * Note: cautious drivers should slow down for organge, but
 * aggresive drivers may choose to "run" orange lights.
 */
typedef struct Car {
    Point location;
    Direction direction;
    int speed; //km/h
    char * plate; //This is the cars ID number or licence plate
    int red; //this is a boolean and it tells the current car that the light for the intersection that it is approaching is red
    int orange; //this is a boolean and it tells the current car that the light for the intersection that it is approaching is orange
    int invisible; //This is a boolean value and it sets the car to be dimenionless/invisible. This is used instead of the leader car to stop other cars
} Car;

typedef struct Intersection {
    Point origin;
    float width;
    float height;

} Intersection;

/**
 * This struct describes the positions of a lane
 * A horizontal lane will have identical y co-ords
 * A vertical lane will have identical x co-ords
 */
typedef struct Lane {
	Direction direction;
	Point start_pos;
	Point end_pos;
	float density; //This describes how many cars should be on this lane
} Lane;


#define MAX_CARS 100 //Entire array of cars is statically allocated
#define NUM_OF_LANES 4

Lane all_lanes[NUM_OF_LANES]; //all lanes in the simulation. Used to determine where to spawn cars and where to destroy them and how many to spawn

Car all_cars[MAX_CARS]; //this array contains all the cars in the simulation
int actual_num_of_cars = 0; //This is how many cars are currently in the simulation

const float CAR_LENGTH = 40;
const float CAR_WIDTH = 20;

int global_speed_limit = 50; //this is in km/h and can vary between 50 and 100;

Intersection* intersections;
int number_of_intersections = 0;
int max_number_of_intersections = 0;

int to_continue = 1;


/*----------Function Prototypes----------*/

void spawn_zero_dim_car(Point location);
void remove_zero_dim_car(Point location);

#endif
