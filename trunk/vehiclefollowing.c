//This file is the main file for vehicle folloiwng

#include globals.h

int MAP_X_MAX = 1000;
int MAP_Y_MAX = 1000;

int ACCEL = 5; //km/h/tick
int DECEL = 5; //km/h/tick

void init()
{
	//read input file here.
		//how many cars to make for this simulatoin (possibly as a density)
		//input file sanitization -- check that numbers are inside limits
	//assume that input file will not change for entire simulatoion
	
	//spawn cars
		//init all cars at zero speed (they can accelerate using following model to road speed limit)

	//generate random 3 letters and digits to make a plate number (check that plate is unique??)
	//place car at start of lane???
	//drive in direction of lane
}

void main() {
	//remove cars when they drive off map
		// * check all positions of cars and test if they are still on a lane

	//add more cars to achieve the stated density
		// *dont spawn new cars very close to others 
		//(check that other cars are some distance away before making more)
	

	/* move all cars */
	int i = 0;
	for (i < actual_num_of_cars; i++)
	{
		move_one_car(all_cars[i]);
	}
}

void update_car_lane(CarLane current_car_lane) {
	//move car forward in the direction it was travellening at the speed it was travelling
}

/**
 * This function determines which car is the next car in front
 */
void determine_car_in_front(Car current_car) {
	//get your own current lane
	//if lane is horizontal then get current position (x co-ord only)
	//if lane is vertical then get current position (y co-ord only)
	
	//search array of cars.
	//get cars in your lane only
	//look for x (or y) co-ords of all other cars in your lane
	//choose car with closest x or y  co-ord
	//if search turns up nothing then set next car dist to infinity
}

