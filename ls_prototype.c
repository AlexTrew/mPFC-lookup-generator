











/*Created By Alex Trew on 13/11/2018

compile using gcc as >gcc -W -Wall ls_prototype -o ls_prototype -lm

*/

#include "stdio.h"
#include "math.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"





double scale;
double _5ht;
double sf;

FILE* f; 


double 
lookup(double _5ht,double max5ht)
{
	return (1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht;

}

int
run(int sf, double scale, double _5ht, int r_delay ,int r_life)
{
	
	bool end = false;
	bool reward_sp = false;
	double pos = 0;
	double x = 1;
	int steps = 0;
	double speed;
	double speed_out;
	int c1 = 0;
	int c2 = 0;
	
	printf("\n\n\nRun with scaling factor %d, scale length %g, reward delay %d, reward lifetime %d\n\n\n",sf,scale,r_delay,r_life);
	printf("__________________________________________________________________________\n\n\n\n");

	fprintf(f,"\n\n\nRun with scaling factor %d, scale length %g, reward delay %d, reward lifetime %d\n\n\n",sf,scale,r_delay,r_life);
	fprintf(f,"__________________________________________________________________________\n\n\n\n");
	
	while(!end)
	{	

		if(pos<=scale)
		{

			speed = lookup(_5ht, x);
			
			speed_out = sf*speed;
			pos+=(speed_out);
			steps++;
			c1++;
			if(c1>=r_delay)
			{
				if(c2==0)
				{	
					reward_sp = true;
					printf("-------------------reward has spawned!-------------------\n");
					fprintf(f,"-------------------reward has spawned!-------------------\n");
					x=2;
				}
				c2++;
				if(reward_sp==true && c2>=r_life)
				{
					reward_sp = false;
					printf("-------------------reward has despawned!-------------------\n");
					fprintf(f,"-------------------reward has despawned!-------------------\n");
				} 
			}
			printf("step : %i, position: %lf, speed:, %lf, 5ht: %g, vis: %g\n",steps ,pos, speed_out, _5ht, x);
		fprintf(f,"step : %i, position: %lf, speed:, %lf, 5ht: %g, vis: %g\n",steps ,pos, speed_out, _5ht, x);
		}
		else
		{
				
				fprintf(f,"\n\n\n ...done\n");
				printf("\n\n\n ...done\n");
				if(reward_sp)
				{
					printf("reward was successfully collected!\n\n");
					fprintf(f,"reward was successfully collected!\n\n");
				}
				else
				{
					printf("reward was not successfully collected!\n\n");
					fprintf(f,"reward was not successfully collected!\n\n");
				}
				end = true;
		}

		

		
	}
	

	
	return 0;
}

int 
fileOut(char* name)
{
	strtok(name, "\n");
	strcat(name,".txt");
	f = fopen(name, "w");
	return 0;
}

int 
quit(char* str)
{

		
	//	printf("%i, %s, %s\n",strcmp("quit\n",str), "quit",str);

		if(strcmp(str,"quit\n") == 0)
		{
			printf("quitting...");
			printf("cheerio\n\n\n");
			if(f!=NULL)fclose(f);
			return 1;
			
		}
		return 0;
}




int
main()
{

	bool prog = true;
	char scale_in[16];
	char _5ht_in[16];
	char sf_in[16];
	char rs_in[16];
	char rl_in[16];
	char fname_in[256];


	bool first = true;

	printf("Welcome to Alex's mPFC activity measurement prototype! Type \"quit\" to quit.\n\n");	
	

	while(true)
	{

		if(first)
		{

			printf("Enter a name for the output file\n\n>");
			fgets(fname_in,256,stdin);
			if(quit(fname_in)==1)return 0;

			fileOut(fname_in);
			first=false;
		}

		printf("Enter the size of the movement scale\n\n>");
		fgets(scale_in,256,stdin);


		if(quit(scale_in)==1)return 0;
	
		
		printf("Enter the max 5ht value\n\n>");
		fgets(_5ht_in,256,stdin);		

		if(quit(_5ht_in)==1)return 0;

		while(prog)
		{

			printf("Enter a speed scaling factor (Must be a factor/multiple of 10 and > 0)\n\n>");

			fgets(sf_in, 256, stdin);
			if(quit(sf_in)==1)return 0;
			
			if((atof(sf_in) != 1 && fmod(atof(sf_in), 10) != 0)|| atof(sf_in)==0 || atof(sf_in)<0)
			{
				printf("\nInvalid input.\n\n");
			}
			
			else
			{
				prog = false;
			}

			

			
		}

		printf("Enter a reward spawning delay. \n\n>");
		fgets(rs_in,256,stdin);

		if(quit(rs_in)==1)return 0;

		printf("Enter a reward lifetime\n\n>");
		fgets(rl_in,256,stdin);

		if(quit(rl_in)==1)return 1;

		run(atoi(sf_in),atof(scale_in), atof(_5ht_in), atoi(rs_in), atoi(rl_in));






		
		
		
	}



}
