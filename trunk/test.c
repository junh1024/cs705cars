#include <stdio.h>
#include <string.h>
#include <math.h>

float car1pos=-5;
float car2pos=-20;

int car1speed=0;
int car2speed=0;

float anumber;

int i=0;

FILE * iFile, * oFile;

int main (int argc, char* argv[])
{

	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	i=0;
	while ( fscanf(iFile,"%f",&anumber) != EOF )//car1pos
	{
		car1pos=anumber;
		if(fabs(car2pos-car1pos )< 7)//smaller than 7 meters abs distace to car1
		{				
			car2speed=-15; //slow down
		}
		else
		{
			car2speed+=5;//speed up
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
