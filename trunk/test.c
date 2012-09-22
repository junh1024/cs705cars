#include <stdio.h>
float car1pos[110];
float car1speed[110];
float car2pos[200];
float car2speed[200];
float car2initpos=-20;


int i=0;

FILE * iFile, * oFile;

float anumber=0;
int main (int argc, char* argv[])
{
	float lag=1.5;
	int lagread=lag*10;
	float car1posbuf[lagread];
	float car1speedbuf[lagread];
	
	
	iFile = fopen (argv[1],"r");
	oFile = fopen (argv[2],"w+");
	
	while ( fscanf(iFile,"%f",&anumber) != EOF )//100 lines
	{
		car1pos[i]=anumber;
		car1speed[i]=car1pos[i]-car1pos[i-1];
		if(car1speed[i]<0)
			car1speed[i]=0;
		fprintf(oFile,"%f\n",car1speed[i]);
		// printf("%d\r\n",lagread);
		// printf("%f\r\n",anumber);
		// printf("%f\r\n",car1speed[i]);
		// printf("%f\r\n",car1pos[i]);
		i++;
		
	}
		
	
	fclose(iFile);
	fclose(oFile);
	return 0;
}
