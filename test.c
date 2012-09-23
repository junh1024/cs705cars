#include <stdio.h>
#include <string.h>
#include <math.h>
#define cardatalen 200
float car1pos[cardatalen];
float car1speed[cardatalen];
#define lagread 15
#define lag 1.5
#define car2initpos -20

int i=0;
int j=0;
float temp;

FILE * iFile, * oFile;

float anumber=0;
int main (int argc, char* argv[])
{
	// float lag=1.5;
	// int lagread=lag*10;
	// float car1posbuf[lagread]={[0 ... lagread-1]-5.0};
	float car1posbuf[lagread];//lagged car1pos buffer for reading by car 2
	float car1speedbuf[lagread];
	
	// float car2initpos=-20;
	float car2pos[cardatalen]={car2initpos};
	float car2speed[cardatalen]={0,0};
	
	for (i = 0; i < lagread; i++)
		{car1posbuf[i] = -5;}//initialize buffer with car1initialposition
	
	// for (i = 0; i < lagread; i++)
		// {car2pos[i] = -20;}
	
	// for (i=0;i<lagread,i++)

	// memset(car2speed, 0, lagread*sizeof(float));
	// memset(car2pos, car2initpos, car2datalen*sizeof(float));

	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	i=0;
	while ( fscanf(iFile,"%f",&anumber) != EOF )//200 lines
	{
		
		car1pos[i]=anumber;//store car1position in array
		car1speed[i]=car1pos[i]-car1pos[i-1]; //compute car1speed
		if(car1speed[i]<0)
			car1speed[i]=0;
		// fprintf(oFile,"%f\n",car1speed[i]);
		
		// fprintf(oFile,"%f\n",car1pos[i]);

		i++;
		
	}
	
			// printf("%d\r\n",lagread);
		// printf("%f\r\n",anumber);
		// printf("%f\r\n",car1speed[i]);
		// printf("%f\r\n",car1pos[i]);
		



	// for(i=0;i<15;i++)//bulid data
	// {

		// car1posbuf[i]=car1pos[i];
	// }
	for(i=0;i<cardatalen;i++)//perform simulation
	{
		for(j=0;j<lagread-1;j++)//shift car1posbuffer by 1 to left
		{
			car1posbuf[j]=car1posbuf[j+1];
		}
		car1posbuf[lagread-1]=car1pos[i]; //insert most recent car1pos on right
		
		// car2speed[]
		

		if(i!=cardatalen-1)
			{
				
				
				if(fabs(car2pos[i]-car1posbuf[0] )< 5)//smaller than 5 meters abs distace to car1
				{	
					
					car2speed[i+1]=car2speed[i]-0.2; //slow down
					if(car2speed[i+1]<0) //can't have negative speed
						{car2speed[i+1]=0;}
					
					
				}
				else
				{
					if (car2speed[i]>=1.6)//over speed limit, 16cm per 0.1s=1.6m for 1s assume speed limit for road is 60kmh =~1.67m/0.1s
					{	car2speed[i+1]=1.6;}
					else
					{	car2speed[i+1]=car2speed[i]+0.1;}//speed up
				}
				car2pos[i+1]=car2pos[i]+car2speed[i+1];
				
			}//compute the next car position based on this speed
	}
	
		// memmove(car1posbuf,car1posbuf+1,10);
		// car1posbuf[i]=car1pos[i];//set last value to most recent
		// printf("%f\r\n",car1posbuf[0]);
		// printf("%f\r\n",car1posbuf[14]);
		// printf("%f\r\n",car1posbuf[13]);
		// printf("%f\r\n",car1pos[i]);
		
		// car1posbuf[0];
	// }
	
	
		// fprintf(oFile,"%f\n",car2pos[i]);
	
		for(i=0;i<lagread;i++)
		{
			printf("%f\r\n",car1posbuf[i]);
		}
	
		for(i=0;i<cardatalen;i++)
		{
			fprintf(oFile,"%f\n",car2pos[i]);
		}
		
		for(i=0;i<cardatalen;i++)
		{
			fprintf(oFile,"%f\n",car2speed[i]);
		}
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
