//testdrive.c
//
// This program initialises a road layout containing 1 intersection
// It is setup as per testdriveinfo.txt
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

void update_car_lane(LaneOfCars current_car_lane);
void print_all_lanes();
void print_all_cars();

void main() {
	int i;
	for (i = 0; i < NUM_OF_LANES; i++) {
		all_lanes[i].laneID = i+1;
		all_lanes[i].density = 10;
	}
	print_all_lanes();
	print_all_cars();
}

void update_car_lane(LaneOfCars current_car_lane) {
	//move car forward in the direction it was travellening at the speed it was travelling
}

void print_all_lanes() {
	int i;
	printf("===========================\n");
	printf("all_lanes:\n");
	for (i = 0; i < NUM_OF_LANES; i++) {
		printf("laneID: %d - density: %f\n", all_lanes[i].laneID, all_lanes[i].density);
	}
	printf("===========================\n\n");
}

void print_all_cars() {
	printf("===========================\n");
	printf("all_cars:\n");
	printf("===========================\n\n");
}

