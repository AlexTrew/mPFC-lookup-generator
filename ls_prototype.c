











/*Created By Alex Trew on 13/11/2018

compile using gcc as >gcc -W -Wall ls_prototype -o ls_prototype -lm

*/

#include "stdio.h"
#include "math.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include <time.h>





double scale;
double _5ht;
double sf;

FILE* f; 
FILE* r;




double 
lookup(double _5ht,double max5ht, bool nutt)
{
    if(!nutt)
    {
     return (1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht;   
    }
    
     return (1-exp(-pow(max5ht/_5ht,_5ht)))*(_5ht+1);

}

int
run(int sf, double scale, double _5ht, int r_delay ,int r_life)
{
	
	bool end = false;
	bool reward_sp = false;
    bool reward_dsp;
	double pos = 0;
	double x = 1;
	int steps = 0;
	double speed;
	double speed_out;
	int c1 = 0;
	int c2 = 0;
	
	//printf("\n\n\nRun with scaling factor %d, scale length %g, reward delay %d, reward lifetime %d\n\n\n",sf,scale,r_delay,r_life);
	//printf("__________________________________________________________________________\n\n\n\n");

	fprintf(f,"\n\n\nRun with scaling factor %d, scale length %g, reward delay %d, reward lifetime %d\n\n\n",sf,scale,r_delay,r_life);
	fprintf(f,"__________________________________________________________________________\n\n\n\n");
	
	while(!end)
	{	

		if(pos<=scale)
		{

			speed = lookup(_5ht, x, false);
			
			speed_out = sf*speed;
			pos+=(speed_out);
			steps++;
			c1++;
			if(c1>=r_delay)
			{
				if(c2==0)
				{	
					reward_sp = true;
			//		printf("-------------------reward has spawned!-------------------\n");
					fprintf(f,"-------------------reward has spawned!-------------------\n");
					x=2;
				}
				c2++;
				if(reward_sp==true && c2>=r_life)
				{
					reward_sp = false;
                    reward_dsp = true;
			//		printf("-------------------reward has despawned!-------------------\n");
					fprintf(f,"-------------------reward has despawned!-------------------\n");
				} 
			}
		//	printf("step : %i, position: %lf, speed:, %lf, 5ht: %g, vis: %g\n",steps ,pos, speed_out, _5ht, x);
		fprintf(f,"step : %i, position: %lf, speed:, %lf, 5ht: %g, vis: %g\n",steps ,pos, speed_out, _5ht, x);
		}
		else
		{
				
				fprintf(f,"\n\n\n ...done\n");
			//	printf("\n\n\n ...done\n");
				if(reward_sp)
				{
			//		printf("reward was successfully collected!\n\n");
					fprintf(f,"reward was successfully collected!\n\n");
                    
				}
				else if(!reward_dsp && reward_sp)
				{
			//		printf("reward was not successfully collected!\n\n");
					fprintf(f,"reward was not successfully collected!\n\n");
				}
				else if(reward_dsp)
				{
			//		printf("reward was not successfully collected!\n\n");
					fprintf(f,"reward was not successfully collected!\n\n");
				}
				end = true;
		}    





		
		
		
	//}

		

		
	}
	

	
	return 0;
}

int 
fileOut()
{
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    char logname[sizeof("log%d-%d-%d %d:%d:%d.txt")] = "log";
    char resultname[sizeof(("results%d-%d-%d %d:%d:%d.txt"))] = "results";
    char* date = malloc(sizeof("%d-%d-%d %d:%d:%d"));
    
    sprintf(date, "%d-%d-%d %d:%d:%d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcat(logname, date);
    strcat(logname, ".txt");
    strcat(resultname, date);
    strcat(resultname, ".txt");
	f = fopen(logname, "w");
    r = fopen(resultsname, "w");
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
    
    char fname_in[256];
    char scale_in[64];
    char sp_delay_in[64];
    char reward_life_in[64];
    char _5ht_in[4];
    
    double _5ht;

	bool prog = true;

    
    fileOut();



	printf("Welcome to Alex's mPFC activity measurement prototype! Type \"quit\" to quit.\n\n");	
	

	//while(true)
	//{


    printf("Enter 5ht value or \"quit\" to quit\n\n>");
    fgets(_5ht_in,256,stdin);
    if(quit(_5ht_in)==1)return 0;
        
    _5ht = atof(_5ht_in);
		
    printf("Enter max scale length, or type \"quit\" to quit\n\n>");
    fgets(scale_in,256,stdin);
    if(quit(scale_in)==1)return 0;
        
        
    printf("Enter a max reward spawning delay, or type \"quit\" to quit\n\n>");
    fgets(sp_delay_in, 256, stdin);
    if(quit(sp_delay_in)==1)return 0;
        
    printf("Enter a max reward lifetime, or type \"quit\" to quit \n\n>");
        
    fgets(reward_life_in, 256, stdin);
    if(quit(reward_life_in)==1)return 0;
        
    printf("calculating scaling...");
        
    for(int sl = 10; sl<=atoi(scale_in); sl=sl+10 ) //for scale lengths
    {
        for(int rs = 1; rs<=atoi(sp_delay_in); rs++) //for 
        {
            for(int rd = 1; rd<=atoi(reward_life_in); rd++)
            {
                    run(10, (double)sl, (double)_5ht, (double)rs, (double)rd);
            }
        }
    }
        
    printf("done\n\n");
   




}
