#include <stdio.h>
#include <string.h>
#define car1datalen 110
#define car2datalen 200
float car1pos[car1datalen];
float car1speed[car1datalen];
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
	float car1posbuf[lagread];
	float car1speedbuf[lagread];
	
	// float car2initpos=-20;
	float car2pos[200]={car2initpos};
	float car2speed[200]={0};
	
	for (i = 0; i < lagread; i++)
		{car1posbuf[i] = -5;}
	
	// for (i=0;i<lagread,i++)

	// memset(car2speed, 0, lagread*sizeof(float));
	// memset(car2pos, car2initpos, car2datalen*sizeof(float));

	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	i=0;
	while ( fscanf(iFile,"%f",&anumber) != EOF )//100 lines
	{
		
		car1pos[i]=anumber;
		car1speed[i]=car1pos[i]-car1pos[i-1];
		if(car1speed[i]<0)
			car1speed[i]=0;
		fprintf(oFile,"%f\n",car1speed[i]);
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
	for(i=0;i<2;i++)
	{
		for(j=0;j<14;j++)//shift
		{
			car1posbuf[j]=car1posbuf[j+1];
		}
		car1posbuf[14]=car1pos[i];
	}
	
		// memmove(car1posbuf,car1posbuf+1,10);
		// car1posbuf[i]=car1pos[i];//set last value to most recent
		// printf("%f\r\n",car1posbuf[0]);
		// printf("%f\r\n",car1posbuf[14]);
		// printf("%f\r\n",car1posbuf[13]);
		// printf("%f\r\n",car1pos[i]);
		
		// car1posbuf[0];
	// }
	
	
	
	
		for(i=0;i<lagread;i++)
		{
		printf("%f\r\n",car1posbuf[i]);
		}
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
