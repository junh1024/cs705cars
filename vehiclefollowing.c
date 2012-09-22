//This file is the main file for vehicle folloiwng

#define MAX_CARS 100
#define NUM_OF_LANES 1 //Start by getting this to work on a single lane

int actual_num_of_cars = 5;
int MAP_X_MAX = 1000;
int MAP_Y_MAX = 1000;

//This structs describes the positions of a lane
//It includes the start and end of each lane
//A horizontal lane will have identical y co-ords
//A vertical lane will have identical x co-ords
//this is somewhat inefficient
typedef struct {
	int direction;
	int postion_x_start;
	int postion_x_end;
	int postion_y_start;
	int postion_y_end;
} lane;

lane all_lanes[NUM_OF_LANES]

typedef struct {
	int speed;
	int posx;
	int posy;
	int direction;
	char * platenumber;
	int VTL_stop;
	int VTL_slow;
	int VTL_go;
 //possibly flags?
} car;

car all_cars[MAX_CARS]; //this array contains all the cars in the simulation

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
	

	/* move all cars
     * THIS IS NOT CALLED BY US
     * CALLED BY VTL PEOPLE. WILL LOOK SOMETHING LIKE THIS
	*/
	int i = 0;
	for (i < actual_num_of_cars; i++)
	{
		process_VTL(/* VTL signals */, all_cars[i])
	}


}

void process_VTL(int stop, int go, int slow, car current_car) {
	//figure out what to do
	//there may not be *ANY* signals here. we might not be near an intersection
	move_one_car(1, car current_car); //always go
}


void move_one_car(int operate, car current_car) {
	//follow the model that we choose
	if (!operate) {
		//decelerate
	}
	else {
		//run car following model
	}
}
		




