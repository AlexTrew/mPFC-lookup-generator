


#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"
#include "string.h"



double 
lookup(double _5ht,double max5ht, bool nutt)

{
	if(!nutt) return (1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht; //nutt version with 5ht offset;
    return (1-exp(-pow(max5ht/_5ht,_5ht)))*(_5ht+1); //standard version with no 5ht offset;

}

int 
tabulate(double inc, double max5ht)
{
    printf("Standard ls model: \n\n");
	printf("\n\n\n   5ht	|	x	| standard output   | nutt output\n_________________________________________________________\n");
	for(double _5ht=0;_5ht<=max5ht;_5ht+=inc)
	{

		for(int x=0;x<=3;x++)
		{		
			printf("%.1lf	|	%d	|	%lf    |  %lf  \n",_5ht,x,lookup(_5ht,x, false), lookup(_5ht,x, true));
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


