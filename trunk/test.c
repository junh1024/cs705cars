#include <stdio.h>
#include <string.h>
#include <math.h>

float car1pos=-5;
float car1prevpos=-5;

float car2pos=-20;
float car2prevpos=-20;

int car1speed=0;
int car2speed=0;
int car1prevspeed=0;
int car2prevspeed=0;

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
		if(fabs(car2pos-car1pos )< 5)//smaller than 5 meters abs distace to car1
		{	
			
			car2speed=car2prevspeed-10; //slow down
			if(car2speed<0) //can't have negative speed
				{car2speed=0;}
		}
		else
		{
			if (car2prevspeed>=60)//over speed limit, 16cm per 0.1s=1.6m for 1s assume speed limit for road is 60kmh =~1.67m/0.1s
			{	car2speed=60;}
			else
			{	car2speed=car2prevspeed+5;}//speed up
		}
		car2pos=car2prevpos+(car2speed/3.6);
		car2prevpos=car2pos;
		car2prevspeed=car2speed;
		
		fprintf(oFile,"%f\n",car2pos);
		// fprintf(oFile,"%f\n",car2prevpos);
		// fprintf(oFile,"%f\n",car2speed);
		// fprintf(oFile,"%f\n",car2prevspeed);
		
		
	}
	

	
		// for(i=0;i<lagread;i++)
		// {
			// printf("%f\r\n",car1posbuf[i]);
		// }
	
		// for(i=0;i<cardatalen;i++)
		// {
			// fprintf(oFile,"%f\n",car2pos[i]);
		// }
		
		// for(i=0;i<cardatalen;i++)
		// {
			// fprintf(oFile,"%f\n",car2speed[i]);
		// }
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
