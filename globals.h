#ifndef VTL_GLOBALS_H
#define VTL_GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //allows using bool, true and false


#define MAX_CARS_PER_LANE 100 //Entire array of cars is statically allocated
#define NUM_OF_LANES 8


typedef enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SN = UP,    // South to north
    NS = DOWN,  // North to south
    EW = LEFT,  // East to west
    WE = RIGHT  // West to east
} Direction;

typedef enum TurnIntention {
    LEFT_TURN,
    RIGHT_RIGHT,
    STRAIGHT
} TurnIntention;

typedef struct Point {
    float x;
    float y;
} Point;

/**
 * This structure represents a single car in the simulation
 * Each car has its own signals for red and orange internally.
 * Orange is currently unused but may be used later.
 * Note: cautious drivers should slow down for organge, but
 * aggresive drivers may choose to "run" orange lights.
 *
 * Invisible cars are placed at the "stop line" of the
 * intersection to cause other cars to stop
 * This is used instead of the leader car to stop other cars
 */
typedef struct Car {
    Point location;
    int speed; //km/h
    char * plate; //This is the cars ID number or licence plate
    bool red; //tells the current car that the light for the intersection that it is approaching is red
    bool orange; //tells the current car that the light for the intersection that it is approaching is orange
    bool invisible; //sets the car to be dimenionless/invisible.
	TurnIntention turn_intention;
} Car;

/**
 * All cars are associated with a lane. Lanes have direction.
 * Cars in a lane will always be travelling in the direction of the lane
 * Presently there is only one intersection in the simulation
 * Thus there are only 8 possible lanes.
 * Each lane has an ID number assigned as per <document>
 * The car at the "front" of the lane ie. closest to the next intersection is at start_index
 * The last car in the queue of cars on this lane is at end_index
 */
typedef struct LaneOfCars {
    Car cars[MAX_CARS_PER_LANE]; //all the cars in any single lane. This is a circular array??
    int start_index;
    int end_index;
    Direction direction;
    int lane_id;
} LaneOfCars;

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
	int laneID;
	Direction direction;
	Point start_pos;
	Point end_pos;
	float density; //This describes how many cars should be on this lane
} Lane;

//all lanes in the simulation.
//Used to determine where to spawn cars and where to destroy them and how many to spawn
Lane all_lanes[NUM_OF_LANES]; 

LaneOfCars all_cars[NUM_OF_LANES]; //this array contains all the lane of cars in the simulation

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
