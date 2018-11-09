


#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"
#include "string.h"

double 
lookup(double _5ht,double max5ht)
{
	return (1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht;

}

int 
tabulate(double inc, double max5ht)
{

	printf("\n\n\n   5ht		|	x	|	output\n________________________________________________\n");
	for(double _5ht=0;_5ht<=max5ht;_5ht+=inc)
	{

		for(int x=0;x<=3;x++)
		{		
			printf("%.1lf	|	%d	|	%lf\n",_5ht,x,lookup(_5ht,x));
		}
		
	}
	printf("\n\n\n");
	return 0;
}


int
main()
{
	bool quit = false;

	char _5ht_in[4];
	char max5ht_in[4];
	char* qstr = "quit";

	double max5ht;
	double _5ht;

	printf("Welcome to Alex's 5ht lookup program.\n");

	while(!quit)
	{
		printf("Enter the value by which _5ht should increment in row of the lookup table, or type \"quit\" to exit.\n>");

		fgets(_5ht_in, 5 ,stdin);

		if(strcmp(qstr,_5ht_in) == 0)
		{
			printf("quitting...");
			quit = true;
			printf("cheerio\n\n\n");
			break;
		}


		printf("enter an maximum 5ht value or type \"quit\" to exit.\n>");

		fgets(max5ht_in, 5, stdin);

		if(strcmp(qstr,max5ht_in) == 0)
		{
			printf("quitting...");
			quit = true;
			printf("cheerio\n\n\n");
			break;
					
		}

		_5ht = atof(_5ht_in);
		max5ht = atof(max5ht_in);
		tabulate(_5ht,max5ht);
	
		
	}
	return 0;
}


