/**
 * testdrive.c
 * 
 * @author:               Devin Barry
 * @date:                 28.09.2012
 * @last modififed        29.09.2012
 * @description
 * 
 * This program initialises a road layout containing 1 intersection
 * The intersection is setup as per testdriveinfo.txt
 *
 * A very simple drive path is tested which uses only two lanes
 * These lanes are connected directly to each other as follows
 *
 *
 *    ==============================        ===================================
 *
 *
 *                                                           ^This is lane ID 3
 *    ^Above here is lane ID 1       ^intersection
 *
 *
 * A car will drive from the beginning of lane 1 across the intersection into lane 3
 * 
 * 
 */

#include "globals.h"
#include "vehiclefollowing.h"
#include <stdio.h>
#include <time.h>

#define TOTAL_TICKS 20


/*------------Function Prototypes-----------*/

void init_lanes();
void init_lanes_of_cars();
void update_car_lane(LaneOfCars *current_car_lane);

void car_following_model(Car *currentCar, Car *carInFront);
void leader_car_model(Car *currentCar);

void print_all_lanes();
void print_all_cars();
void print_car(Car car);
char * get_direction_string(Direction direction);
char * get_compass_direction_string(Direction direction);
char * get_point_string(Point point);

/*----------End Function Prototypes----------*/

int main() {
	init_lanes();
	init_lanes_of_cars();
	//print_all_lanes();
	//print_all_cars();
	int i;
	for (i = 0; i < TOTAL_TICKS; i++) {
		printf("=====   Tick %d\n\n", i+1);
		update_car_lane(&all_cars[0]);
	}
	return 0;
}

//This function sets up all the lanes so that we can test our car
//following model
void init_lanes() {
	int i;
	for (i = 0; i < NUM_OF_LANES; i++) {
		all_lanes[i].lane_id = i;
		all_lanes[i].density = 10;
	}
	//lane 0
	all_lanes[0].direction = RIGHT;
	all_lanes[0].start_pos.x = 0;
	all_lanes[0].start_pos.y = 20;
	all_lanes[0].end_pos.x = 50;
	all_lanes[0].end_pos.y = 20;
	//lane 1
	all_lanes[1].direction = LEFT;
	all_lanes[1].start_pos.x = 0;
	all_lanes[1].start_pos.y = 20;
	all_lanes[1].end_pos.x = 50;
	all_lanes[1].end_pos.y = 20;
	//lane 2
	all_lanes[2].direction = RIGHT;
	all_lanes[2].start_pos.x = 0;
	all_lanes[2].start_pos.y = 20;
	all_lanes[2].end_pos.x = 50;
	all_lanes[2].end_pos.y = 20;
	all_lanes[3].direction = LEFT;
	all_lanes[3].start_pos.x = 0;
	all_lanes[3].start_pos.y = 20;
	all_lanes[3].end_pos.x = 50;
	all_lanes[3].end_pos.y = 20;
	all_lanes[4].direction = UP;
	all_lanes[4].start_pos.x = 0;
	all_lanes[4].start_pos.y = 20;
	all_lanes[4].end_pos.x = 50;
	all_lanes[4].end_pos.y = 20;
	all_lanes[5].direction = DOWN;
	all_lanes[5].start_pos.x = 0;
	all_lanes[5].start_pos.y = 20;
	all_lanes[5].end_pos.x = 50;
	all_lanes[5].end_pos.y = 20;
	all_lanes[6].direction = UP;
	all_lanes[6].start_pos.x = 0;
	all_lanes[6].start_pos.y = 20;
	all_lanes[6].end_pos.x = 50;
	all_lanes[6].end_pos.y = 20;
	all_lanes[7].direction = DOWN;
	all_lanes[7].start_pos.x = 0;
	all_lanes[7].start_pos.y = 20;
	all_lanes[7].end_pos.x = 50;
	all_lanes[7].end_pos.y = 20;
}

//This function inits all the car lanes
void init_lanes_of_cars() {
	int i, j;
	for (i = 0; i < NUM_OF_LANES; i++) {
		all_cars[i].lane_id = all_lanes[i].lane_id; //here we copy the lane ID from all_lanes
		all_cars[i].start_index = 0;
		all_cars[i].end_index = 0;
		all_cars[i].count = 0;
		all_cars[i].direction = all_lanes[i].direction; //get the direction from the corresponding lane
		for (j = 0; j < MAX_CARS_PER_LANE; j++) {
			all_cars[i].cars[j].location.x = 0;
			all_cars[i].cars[j].location.y = 0;
			all_cars[i].cars[j].speed = 0;
			all_cars[i].cars[j].plate = "000000";
			all_cars[i].cars[j].red = false;
			all_cars[i].cars[j].orange = false;
			all_cars[i].cars[j].invisible = false;
			all_cars[i].cars[j].turn_intention = STRAIGHT;
			all_cars[i].cars[j].lane_id = all_lanes[i].lane_id; //here we copy the lane ID from all_lanes
		}
	}
	
	/*===================== HERE WE CREATE 2 CARS MANUALLY (in lane 0) ===================================*/
	//give car1 a plate
	all_cars[0].cars[all_cars[0].end_index].plate = "ABC123";
	//place that car at location on the lane that it is supposed to spawn on
	all_cars[0].cars[all_cars[0].end_index].location.x = all_lanes[0].start_pos.x;
	all_cars[0].cars[all_cars[0].end_index].location.y = all_lanes[0].start_pos.y;
	all_cars[0].cars[all_cars[0].end_index].speed = 50; //start immediately at speed
	all_cars[0].end_index++; //Tells people there is one more car in the array
	all_cars[0].count++; //Without changing these two variables things will break
	
	//give car2 a plate
	all_cars[0].cars[all_cars[0].end_index].plate = "DEF456";
	//place that car at location on the lane that it is supposed to spawn on
	all_cars[0].cars[all_cars[0].end_index].location.x = all_lanes[0].start_pos.x;
	all_cars[0].cars[all_cars[0].end_index].location.y = all_lanes[0].start_pos.y;
	all_cars[0].cars[all_cars[0].end_index].speed = 40; //start immediately at speed
	all_cars[0].end_index++;
	all_cars[0].count++;
}

//This function will update the positions of all cars in a certain lane
void update_car_lane(LaneOfCars *current_car_lane) {
	int i;
	int startIndex = current_car_lane->start_index;
	int endIndex = current_car_lane->end_index;
	
	/**
	 * This loop comes from the macro defined in globals.h
	 * It ensures that the circular buffer is always iterated in the correct
	 * order. The car at the front (closest to the intersection) of the lane
	 * will always occur first in the loop (when i = startIndex). i will
	 * increment through all cars (including possibly wrapping around at the
	 * end of the array and counting up again) untill endIndex is reached.
	 * 
	 * accessing the current car can be done as follows:
	 * current_car_lane->cars[i]            <---This is the current car
	 */
	foreach_car(i, startIndex, endIndex) {
		if (i == startIndex) {
			//do something special because this is the front car in the lane
			leader_car_model(&(current_car_lane->cars[i]));
		}
		else {
			car_following_model(&(current_car_lane->cars[i]), &(current_car_lane->cars[i-1]));
		}
	}
}

/**
 * This function updates the position of the current car, but obeys the car following model
 */
void car_following_model(Car *currentCar, Car *carInFront) {
	int current_x_location = currentCar->location.x;
	current_x_location += currentCar->speed;
	currentCar->location.x = current_x_location;
	
	//the direction of the lane in which this car is in
	Direction current_car_direction = all_lanes[currentCar->lane_id].direction;
	
	print_car(*currentCar); //print data about the current car
	printf("Current Car Direction: %s\n\n", get_compass_direction_string(current_car_direction));
}

/**
 * This function updates the position of the current car assuming it is the leader
 */
void leader_car_model(Car *currentCar) {
	//move car forward in the direction it was travellening at the speed it was travelling
	int current_x_location = currentCar->location.x;
	current_x_location += currentCar->speed;
	currentCar->location.x = current_x_location;
	
	//the direction of the lane in which this car is in
	Direction current_car_direction = all_lanes[currentCar->lane_id].direction;
	
	print_car(*currentCar); //print data about the current car
	printf("Current Car Direction: %s\n\n", get_compass_direction_string(current_car_direction));
}


/*============================ THESE FUNCTIONS ONLY USED FOR DEVINS OUTPUT DISPLAY ===============================*/

void print_all_lanes() {
	int i;
	printf("====================================\n");
	printf("all_lanes:\n");
	for (i = 0; i < NUM_OF_LANES; i++) {
		printf("----------LaneID: %d----------\n", all_lanes[i].lane_id);
		printf("density: %2.0f\n", all_lanes[i].density);
		printf("direction: %s\n", get_direction_string(all_lanes[i].direction));
		printf("start location: %s\n", get_point_string(all_lanes[i].start_pos));
		printf("end location: %s\n", get_point_string(all_lanes[i].end_pos));
	}
	printf("====================================\n\n");
}

void print_all_cars() {
	printf("===========================\n");
	printf("all_cars:\n");
	printf("===========================\n\n");
}

void print_car(Car car) {
	printf("----------Car plate: %s----------\n", car.plate);
	printf("lane ID: %d\n", car.lane_id);
	printf("Current location: %s\n", get_point_string(car.location));
	printf("Current speed: %d\n", car.speed);
	printf("Invisible: %d\n", car.invisible);
}

char * get_point_string(Point point) {
	static char buff[20];
	sprintf(buff, "x=%2.0f, y=%2.0f", point.x, point.y);
	return buff;
}

char * get_direction_string(Direction direction) {
	if (direction == DOWN) return "DOWN";
	if (direction == LEFT) return "LEFT";
	if (direction == RIGHT) return "RIGHT";
	if (direction == UP) return "UP";
	else return "N/A";
}

char * get_compass_direction_string(Direction direction) {
	if (direction == SN) return "SN";                  // South to north
	if (direction == NS) return "NS";                  // North to south
	if (direction == EW) return "EW";                  // East to west
	if (direction == WE) return "WE";                  // West to east
	else return "N/A";
}

