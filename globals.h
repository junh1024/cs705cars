#ifndef VTL_GLOBALS_H
#define VTL_GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> //allows using bool, true and false


#define MAX_CARS_PER_LANE 100 //Entire array of cars is statically allocated
#define NUM_OF_LANES 8


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
    char plate[7]; //This is the cars ID number or licence plate
    bool red; //tells the current car that the light for the intersection that it is approaching is red
    bool orange; //tells the current car that the light for the intersection that it is approaching is orange
    bool invisible; //sets the car to be dimenionless/invisible.
    TurnIntention turn_intention;
    int lane_id; //the lane which this car is in
} Car;

#define increment(i) (++i % MAX_CARS_PER_LANE)
#define compare(i, start, end) (i < end) || (i > start && start > end)
#define foreach_car(i, start, end) for(i = start; (i < end) || ((i >= start) && (start > end)); i = (i+1) % MAX_CARS_PER_LANE)

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
    Car cars[MAX_CARS_PER_LANE]; //all the cars in any single lane. This is a circular array
    int start_index;
    int end_index;
    int count; //the actual number of cars in this lane
    Direction direction;
    int lane_id;
} LaneOfCars;

typedef struct Intersection {
    Point origin;
    float width;
    float height;
    int isGenerated; // Whether the intersection was automatically generated
} Intersection;


// ====================================================================
//INFRASTRUCTURE
// ====================================================================

const float TRAFFIC_LIGHT_WIDTH = 20;
const float TRAFFIC_LIGHT_HEIGHT = 20;

/* Traffic Light State */
typedef enum {
    RED = 0,
    ORANGE = 1,
    GREEN = 2,
}TrafLightState;

typedef struct{
    float xPos;
    float yPos;
    TrafLightState state;
} trafLight;

typedef struct Box {
    Point center;
    float width;
    float height;
    Direction direction;
} Box;

/**
 * This struct describes the positions of a lane
 * A horizontal lane will have identical y co-ords
 * A vertical lane will have identical x co-ords
 */
typedef struct Lane {
    int lane_id;
    Direction direction;
    Point start_pos;
    Point end_pos;
    float density; //This describes how many cars should be on this lane
} Lane;

//========================
// Infrastructure GLOBALS
//========================

/* ---- Go Zone ----*/
// 0 - SN
// 1 - NS
// 2 - EW
// 3 - WE
Box goZone[4];

// Array of lanes. Contains 4 lanes for a single intersection.
// 0 - SN
// 1 - NS
// 2 - EW
// 3 - WE
Lane* lanes;

// Traffic lights for the intersection. 2 Traffic lights per intersction.
// Currently only defines 1 intersection.
trafLight trafLightNS, trafLightEW;

// ====================================================================
//
// ====================================================================

//all lanes in the simulation.
//Used to determine where to spawn cars and where to destroy them and how many to spawn
Lane all_lanes[NUM_OF_LANES];

LaneOfCars all_cars[NUM_OF_LANES]; //this array contains all the lane of cars in the simulation

int actual_num_of_cars = 0; //This is how many cars are currently in the simulation

const float CAR_LENGTH = 40;
const float CAR_WIDTH = 20;

// The dimensions of the map
const float map_width = 2000;
const float map_height = 2000;

const float intersection_width = 100;
const float intersection_height = 100;
const float intersection_padding = 20; // How much gap to leave between intersections

int global_speed_limit = 50; //this is in km/h and can vary between 50 and 100;

Intersection* intersections;
int number_of_intersections = 0;
int max_number_of_intersections = 0;

int to_continue = 1;


/*----------Function Prototypes----------*/

void spawn_zero_dim_car(Point location);
void remove_zero_dim_car(Point location);

int is_almost_equal(float a, float b, float tolerance) {
    return fabs(a - b) <= tolerance;
}

#endif
