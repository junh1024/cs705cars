//testdrive.c
//
// This program initialises a road layout containing 1 intersection
// The intersection is setup as per testdriveinfo.txt
//
// A very simple drive path is tested which uses only two lanes
// These lanes are connected directly to each other as follows
//
//
//          ==============================        ===================================
//
//
//                                                                 ^This is lane ID 3
//          ^Above here is lane ID 1       ^intersection
//
//
// A car will drive from the beginning of lane 1 across the intersection into lane 3

#include "globals.h"
#include "vehiclefollowing.h"
#include <stdio.h>
#include <time.h>

#define TOTAL_TICKS 20

void init_lanes();
void init_lanes_of_cars();
void update_car_lane(LaneOfCars *current_car_lane);
void update_car_location(Car *currentCar);
void print_all_lanes();
void print_all_cars();
void print_car(Car car);
char * get_direction_string(Direction direction);
char * get_point_string(Point point);

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

void init_lanes() {
	int i;
	for (i = 0; i < NUM_OF_LANES; i++) {
		all_lanes[i].lane_id = i+1;
		all_lanes[i].density = 10;
	}
	all_lanes[0].direction = RIGHT;
	all_lanes[0].start_pos.x = 0;
	all_lanes[0].start_pos.y = 20;
	all_lanes[0].end_pos.x = 50;
	all_lanes[0].end_pos.y = 20;
	all_lanes[1].direction = LEFT;
	all_lanes[1].start_pos.x = 0;
	all_lanes[1].start_pos.y = 20;
	all_lanes[1].end_pos.x = 50;
	all_lanes[1].end_pos.y = 20;
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

void init_lanes_of_cars() {
	int i, j;
	for (i = 0; i < NUM_OF_LANES; i++) {
		all_cars[i].lane_id = i+1;
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
		}
	}
	//laneID 1
	
	/*===================== HERE WE CREATE 1 CAR MANUALLY ===================================*/
	//give 1 car a plate
	all_cars[0].cars[all_cars[0].end_index].plate = "ABC123";
	//place that car at location on the lane that it is supposed to spawn on
	all_cars[0].cars[all_cars[0].end_index].location.x = all_lanes[0].start_pos.x;
	all_cars[0].cars[all_cars[0].end_index].location.x = all_lanes[0].start_pos.x;
	all_cars[0].cars[all_cars[0].end_index].speed = 50; //start immediately at speed
	all_cars[0].end_index = 1; //Tells people there is one car in the array
	all_cars[0].count = 1; //Without changing these two variables things will break
}

void update_car_lane(LaneOfCars *current_car_lane) {
	//move car forward in the direction it was travellening at the speed it was travelling
	int i;
	foreach_car(i, current_car_lane->start_index, current_car_lane->end_index) {
		update_car_location(&(current_car_lane->cars[i]));
		print_car(current_car_lane->cars[i]); // <--------- This is the current car
	}
}

void update_car_location(Car *currentCar) {
	int current_x_location = currentCar->location.x;
	current_x_location += currentCar->speed;
	currentCar->location.x = current_x_location;
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
	printf("Current location: %s\n", get_point_string(car.location));
	printf("Current speed: %d\n", car.speed);
	printf("Invisible: %d\n\n", car.invisible);
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


