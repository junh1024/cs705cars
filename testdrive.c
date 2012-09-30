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
 *                                                           ^This is lane ID 2
 *    ^Above here is lane ID 0       ^intersection
 *
 *
 * A car will drive from the beginning of lane 0 across the intersection into lane 2
 * 
 * 
 */

#include "globals.h"
#include "vehiclefollowing.h"
#include <stdio.h>
// #include <time.h>
#include <string.h>
// #include <math.h>

#define TOTAL_TICKS 20


/*------------Function Prototypes-----------*/

void init_lanes();
void init_lanes_of_cars();
void update_car_lane(LaneOfCars *current_car_lane);

void car_following_model(Car *currentCar, Car *carInFront);
void leader_car_model(Car *currentCar);
bool transition_car_to_new_lane(Car *currentCar);
void copy_car_to_new_lane(int current_lane_id, int next_lane_id);

void print_all_lanes();
void print_all_cars();
void print_car(Car car);
char * get_direction_string(Direction direction);
char * get_compass_direction_string(Direction direction);
char * get_point_string(Point point);

void generatecarplate(char* plate);
int isItUnique(char* plate)

/*----------End Function Prototypes----------*/

int main() {
	init_lanes();
	init_lanes_of_cars();
	//print_all_lanes();
	//print_all_cars();
	int i;
	for (i = 0; i < TOTAL_TICKS; i++) {
		printf("=====   Tick %d\n\n", i+1);
		update_car_lane(&all_cars[0]); //we are only updating lane0 and lane2
		update_car_lane(&all_cars[2]);
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
	all_lanes[0].end_pos.x = 600;
	all_lanes[0].end_pos.y = 20;
	//lane 1
	all_lanes[1].direction = LEFT;
	all_lanes[1].start_pos.x = 0;
	all_lanes[1].start_pos.y = 50;
	all_lanes[1].end_pos.x = 600;
	all_lanes[1].end_pos.y = 50;
	//lane 2
	all_lanes[2].direction = RIGHT;
	all_lanes[2].start_pos.x = 650;
	all_lanes[2].start_pos.y = 20;
	all_lanes[2].end_pos.x = 1300;
	all_lanes[2].end_pos.y = 20;
	//lane 3
	all_lanes[3].direction = LEFT;
	all_lanes[3].start_pos.x = 650;
	all_lanes[3].start_pos.y = 50;
	all_lanes[3].end_pos.x = 1300;
	all_lanes[3].end_pos.y = 50;
	
	//lane 4
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
			strcpy(all_cars[i].cars[j].plate, "000000");
			all_cars[i].cars[j].red = false;
			all_cars[i].cars[j].orange = false;
			all_cars[i].cars[j].invisible = false;
			all_cars[i].cars[j].turn_intention = STRAIGHT;
			all_cars[i].cars[j].lane_id = all_lanes[i].lane_id; //here we copy the lane ID from all_lanes
		}
	}
	

	/*===================== HERE WE CREATE 2 CARS MANUALLY (in lane 0) ===================================*/
	//give car1 a plate
	generatecarplate(all_cars[0].cars[all_cars[0].end_index].plate);
	//place that car at location on the lane that it is supposed to spawn on
	all_cars[0].cars[all_cars[0].end_index].location.x = all_lanes[0].start_pos.x;
	all_cars[0].cars[all_cars[0].end_index].location.y = all_lanes[0].start_pos.y;
	all_cars[0].cars[all_cars[0].end_index].speed = 50; //start immediately at speed
	all_cars[0].end_index++; //Tells people there is one more car in the array
	all_cars[0].count++; //Without changing these two variables things will break
	
	//give car2 a plate
	generatecarplate(all_cars[0].cars[all_cars[0].end_index].plate) ;
	//place that car at location on the lane that it is supposed to spawn on
	all_cars[0].cars[all_cars[0].end_index].location.x = all_lanes[0].start_pos.x;
	all_cars[0].cars[all_cars[0].end_index].location.y = all_lanes[0].start_pos.y;
	all_cars[0].cars[all_cars[0].end_index].speed = 0; //start immediately at speed
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
			//right now ONLY the leader car can transition between lanes
			//this means currently only ONE CAR per tick can change lanes
			//if cars are travelling really fast and several change lanes
			//in one tick this method will blow up. Changes are needed here
			//to allow this simulation to deal with multiple cars moving
			//lanes per tick
			if (transition_car_to_new_lane(&(current_car_lane->cars[i]))) 
			{
				continue; //dont update car position if it was moved to a new lane
			}
			
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

	float speedlimit=global_speed_limit;
	float distancetonextcar;
	//the direction of the lane in which this car is in
	Direction current_car_direction = all_lanes[currentCar->lane_id].direction;

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

	print_car(*currentCar); //print data about the current car
	printf("Current Car Direction: %s\n\n", get_compass_direction_string(current_car_direction));
}

/**
 * This function updates the position of the current car assuming it is the leader
 */
void leader_car_model(Car *currentCar) {
	//move car forward in the direction it was travellening at the speed it was travelling
	currentCar->location.x += (currentCar->speed)/3.6;

	
	//the direction of the lane in which this car is in
	Direction current_car_direction = all_lanes[currentCar->lane_id].direction;
	
	print_car(*currentCar); //print data about the current car
	printf("Current Car Direction: %s\n\n", get_compass_direction_string(current_car_direction));
}

/**
 * moves car over an intersection to a new lane
 * --test car position, if it is at the end (or more) of the current lane
 * --move it to the correct place in the next lane
 * 
 * The only problem with this lane move function right now is that it
 * doesn't take into account the size of the intersection. The car
 * "magically" flies over the intersection and even does its normal
 * movement in the next lane during the intersection transition tick
 * This needs to be fixed
 * 
 * @return boolean indicating whether a car was moved to the next lane
 *         or not
 */
bool transition_car_to_new_lane(Car *currentCar) {
	//the direction of the lane in which this car is in
	Direction lane_direction = all_lanes[currentCar->lane_id].direction;
	//the end co-ordinates of the lane in which this car is in
	Point lane_end = all_lanes[currentCar->lane_id].end_pos;
	
	if (lane_direction == WE || lane_direction == EW) {
		//Here lane y-coord SHOULD ALWAYS equal car y-coord
		if (currentCar->location.x >= lane_end.x) {
			//we should move car to next lane
			//this test only uses two lanes so for right now we know that there is only one possible lane transition
			//in the future more code will need to go here to deal with all the other possibilities of lane transitions
			copy_car_to_new_lane(0, 2);
			return true;
		}
		return false; //else its all good
	}
	
	//Currently this will never get called.
	if (lane_direction == SN || lane_direction == NS) {
		//Here lane x-coord SHOULD ALWAYS equal car x-coord
		if (currentCar->location.y >= lane_end.y) {
			//we should move car to next lane
			return true;
		}
		return false; //else its all good
	}
	return false;
}

/**
 * copies the car out of its current lane array and into its new lane array
 */
void copy_car_to_new_lane(int current_lane_id, int next_lane_id) {
	//move car from front of <current_lane_id> to the back of <next_lane_id>
	int current_lane_start_index = all_cars[current_lane_id].start_index;
	int next_lane_end_index = all_cars[next_lane_id].end_index;
	
	//this is the car to be moved
	Car *currentCar = &(all_cars[current_lane_id].cars[current_lane_start_index]);
	//this is the open slot in the next lane
	Car *nextCar = &(all_cars[next_lane_id].cars[next_lane_end_index]);
	
	//Copy all the specs of the "old car" over to the "new car"
	
	strcpy(nextCar->plate, currentCar->plate);
	//cars speed doesnt change as it moves over intersection (maybe it does change in future)
	nextCar->speed = currentCar->speed;
	nextCar->red = currentCar->red;
	nextCar->orange = currentCar->orange;
	nextCar->invisible = currentCar->invisible;
	
	//turn intention might need to change if car has just turned into new lane
	nextCar->turn_intention = currentCar->turn_intention;
	nextCar->lane_id = next_lane_id; //set the lane_id of the "new car" to the next lane
	
	//place the "new car" at the start point of the new lane
	//if the car has "overlapped" the edge of its old lane,
	//it should be moved this far along from its spawn point on the new lane
	//this is a TODO
	nextCar->location.x = all_lanes[next_lane_id].start_pos.x;
	nextCar->location.y = all_lanes[next_lane_id].start_pos.y;
	
	//------------------------TODO--------------------------
	//The incremeneting of decrementing of the indexs
	// are not circular buffer safe. Macros need to be put in here!!!
	
	//These must be incremented to show that the "new car" has turned up in the lane
	all_cars[next_lane_id].end_index++; 
	all_cars[next_lane_id].count++;
	
	//finally the "old car" should be removed from its original lane
	all_cars[current_lane_id].start_index++; //increment start index (car behind old car is now at front)
	all_cars[current_lane_id].count--; //decrease number of cars in this lane
}

/*============================ UTILITY FUNCTIONS ===============================*/
//this function generates a gar plate on the given char pointer
void generatecarplate(char* plate) {
	char letters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i,j; //temp variables
	char h;
	
	for (i=0;i<3;i++) { //generate 3 letters
		j=rand()%25;
		plate[i] = letters[j];
	}
	
	for (i=3;i<6;i++) { //generate 3 numbers
	j=rand()%10;
	h=(char)(((int)'0')+j); 
	plate[i] = h;
	}
	plate[6]='\0'; //null character terminator EOS
  if (isItUnique(plate)==1) {
    old_plates[actual_num_of_cars]=plate;
    return;
  } else {
    generatecarplate(plate);
  }
}

int isItUnique(char* plate) {
  int i,j,check;
  for (i=0; i<actual_num_of_cars; i++) {
    check=0;
    for (j=0; j<6; j++) {
      if (plate[j]==old_plates[i][j]) {
        check++;
      }
    }
    if (check==6) {
      return 0;
    }
  }
  return 1;
}

//spawnornotdensity

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
	sprintf(buff, "x=%2.2f, y=%2.2f", point.x, point.y);
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

