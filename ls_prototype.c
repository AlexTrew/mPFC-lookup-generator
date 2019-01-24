











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
lookup(double _5ht,double max5ht, int type)
{
    switch(type)
    {
        case 1: //control
            return (1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht;
            
        case 2://nutt
            return (1-exp(-pow(max5ht/_5ht,_5ht)))*(_5ht+1);
        
        case 3: //drn supression
            return ((1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht)/10;
        
        case 4: //drn_supression + ssri
            return (((1-exp(-pow(max5ht/_5ht,_5ht)))*_5ht)/10) + 0.5; //TODO experiment 
            
                    
    }
    
     

}

int
simulate(int sf, double scale, double _5ht, int r_delay ,int r_life, int type)
{
	
	
    bool reward_reached = false;
    bool reward_collected = false;
	bool reward_sp = false;
    bool reward_dsp = false;
    double pos = 0;
	double x = 1;
    double speed;
	int steps = 0;
	int c1 = 0;
	int c2 = 0;
	
	//printf("\n\n\nRun with scaling factor %d, scale length %g, reward delay %d, reward lifetime %d\n\n\n",sf,scale,r_delay,r_life);
	//printf("__________________________________________________________________________\n\n\n\n");

	fprintf(f,"\n\n\nRun with scaling factor %d, scale length %g, reward delay %d, reward lifetime %d\n\n\n",sf,scale,r_delay,r_life);
	fprintf(f,"__________________________________________________________________________\n\n\n\n");
    
	
	while(pos<scale)
	{	

		

			
			speed =(sf*lookup(_5ht, x, type));
            
			if(pos<scale)pos+=speed;
            
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
		fprintf(f,"step : %i, position(normal): %lf, speed(normal): %lf, 5ht: %g, vis: %g\n",steps, pos,speed,_5ht,x);
		
		
		if(!reward_reached && pos>=scale)
		{
				
				fprintf(f," Normal agent has reached the reward location.\n");
			//	printf("\n\n\n ...done\n");
				if(reward_sp)
				{
			//		printf("reward was successfully collected!\n\n");
					fprintf(f,"reward was successfully collected by the normal agent!\n\n");
                    reward_collected = true;
				}
				if(!reward_sp && !reward_dsp)
				{
			//		printf("reward was not successfully collected!\n\n");
					fprintf(f,"reward was not spawned when reached by the normal agent!\n\n");
				}
				if(reward_dsp)
				{
					//printf("reward was not successfully collected!\n\n");
					fprintf(f,"reward was not successfully collected by the normal agent!\n\n");
				}
				reward_reached = true;
		}  
		
	}
	

	

	if(reward_collected) return 1;
    
    return 0;
}

int 
fileOut()
{
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    char logname[sizeof("log%d-%d-%d %d:%d:%d.txt")] = "log";
    char resultname[sizeof(("results%d-%d-%d %d:%d:%d.txt"))] = "results";
    char date[sizeof("%d-%d-%d %d:%d:%d")] = "";
    
    sprintf(date, "%d-%d-%d %d:%d:%d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcat(logname, date);
    strcat(logname, ".txt");
    strcat(resultname, date);
    strcat(resultname, ".txt");
	f = fopen(logname, "w");
    r = fopen(resultname, "w");
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

double pythagoras(double s1, double s2)
{
    return sqrt(pow(s1,2) + pow(s2,2));   
}




int
main()
{
    
    char fname_in[256];
    char scale_in[64];
    char sp_delay_in[64];
    char reward_life_in[64];
    char _5ht_in[4];
    char r_in[2];
    char temp[32];
    int result[32];
    double _5ht;
    double rad;

    
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
    
    printf("Enter reward location radius, or type \"quit\" to quit\n\n>");
    fgets(r_in,256,stdin);
    if(quit(r_in)==1)return 0;
    
    rad = atof(r_in); 
        
    printf("calculating scaling...");
    fprintf(r,"Appropriate configurations:\n\n"); 
        
    for(int sl = 10; sl<=atoi(scale_in); sl=sl+10 ) //for scale lengths
    {
        for(double rs = 0; rs<=atoi(sp_delay_in); rs=rs+10) //for 
        {
            for(int rd = 0; rd<=atoi(reward_life_in); rd=rd+10)
            {
                

                result[0] = (simulate(10, (double)sl, (double)_5ht, rs, (double)rd,1)); //normal
                result[1] = (simulate(10, (double)sl-(2*rad), (double)_5ht, rs, (double)rd,1)); //normal(close reward)
                result[2] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, rs, (double)rd,1)); //normal(adjacent reward)
                result[3] = (simulate(10, (double)sl+(2*rad), (double)_5ht, rs, (double)rd,1)); //normal(far reward)
                
                result[5] = (simulate(10, (double)sl, (double)_5ht, (rs/3)*2, (double)rd,1)); //fast reward
                result[6] = (simulate(10, (double)sl-(2*rad), (double)_5ht, (rs/3)*2, (double)rd,1)); //fast reward(close)
                result[7] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, (rs/3)*2, (double)rd,1)); //fast reward(adjacent)
                result[8] = (simulate(10, (double)sl+(2*rad), (double)_5ht, (rs/3)*2, (double)rd,1)); //fast reward(far)
                
                result[9] = (simulate(10, (double)sl, (double)_5ht, rs, (double)rd,2)); //nutt
                result[10] = (simulate(10, (double)sl-(2*rad), (double)_5ht, rs, (double)rd,2)); //nutt(close)
                result[11] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, rs, (double)rd,2)); //nutt(adjacent)
                result[12] = (simulate(10, (double)sl+(2*rad), (double)_5ht, rs, (double)rd,2)); //nutt(far)
                
                result[13] = (simulate(10, (double)sl, (double)_5ht, rs, (double)rd,2)); //nutt + fast reward
                result[14] = (simulate(10, (double)sl-(2*rad), (double)_5ht, rs, (double)rd,2)); //nutt + fast reward(close)
                result[15] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, rs, (double)rd,2)); //nutt + fast reward(adjacent)
                result[16] = (simulate(10, (double)sl+(2*rad), (double)_5ht, rs, (double)rd,2)); //nutt + fast reward(far)
                
                result[17] = (simulate(10, (double)sl, (double)_5ht, rs, (double)rd,3)); //drn supress
                result[18] = (simulate(10, (double)sl-(2*rad), (double)_5ht, rs, (double)rd,3)); //drn supress(close)
                result[19] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, rs, (double)rd,3)); //drn supress(adjacent)
                result[20] = (simulate(10, (double)sl+(2*rad), (double)_5ht, rs, (double)rd,3)); //drn supress(far)    
                
                result[21] = (simulate(10, (double)sl, (double)_5ht, (rs/3)*2, (double)rd,3)); //drn suppress + fast reward
                result[22] = (simulate(10, (double)sl-(2*rad), (double)_5ht, (rs/3)*2, (double)rd,3)); //drn suppress + fast reward(close)
                result[23] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, (rs/3)*2, (double)rd,3)); //drn suppress + fast reward(adjacent)
                result[24] = (simulate(10, (double)sl+(2*rad), (double)_5ht, (rs/3)*2, (double)rd,3)); //drn suppress + fast reward(far)

                result[25] = (simulate(10, (double)sl, (double)_5ht, rs, (double)rd,4)); //drn + ssri
                result[26] = (simulate(10, (double)sl-(2*rad), (double)_5ht, rs, (double)rd,4)); //drn + ssri(close)
                result[27] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, rs, (double)rd,4)); //drn + ssri(adjacent)
                result[28] = (simulate(10, (double)sl+(2*rad), (double)_5ht, rs, (double)rd,4)); //drn + ssri(far)

                        
                result[29] = (simulate(10, (double)sl, (double)_5ht, (rs/3)*2, (double)rd,4)); //drn + ssri + fast reward
                result[30] = (simulate(10, (double)sl-(2*rad), (double)_5ht, (rs/3)*2, (double)rd,4)); //drn + ssri + fast reward(close)
                result[31] = (simulate(10, pythagoras(sl,2*rad), (double)_5ht, (rs/3)*2, (double)rd,4)); //drn + ssri + fast reward(adjacent)
                result[32] = (simulate(10, (double)sl+(2*rad), (double)_5ht, (rs/3)*2, (double)rd,4)); //drn + ssri + fast reward(far)

                
                sprintf(temp, "%d%d%d%d%d%d%d%d",result[0],result[1],result[2],result[3],result[4],result[5],result[6],result[7]);
                if(strcmp("11000000",temp)==0)
                {
                   
                   fprintf(r,"scale length : %d, spawn delay:  %.2lf , reward life: %d. \n\n",sl,rs,rd); 
                   printf("configuration found!: scale length : %d, spawn delay:  %.0lf , reward life: %d. \n\n",sl,rs,rd);
                }
                    
                
            }
        }
    }
    fclose(f);
    fclose(r);
        
    printf("done\n\n");
    
    
   




}


/*
 * TODO
 * 
 * add half 5ht value to default setup. 
 * 
 * reward spawns 1/3 earlier
 * 
 * check out https://github.com/berndporr/limbic-system-simulator/blob/master/limbic-system-simulator.cpp
 * 
 * run with 1/10 5ht (drn supression)
 * 
 * add ssri baseline value to 5ht (0.15)
 * 
 * add drn offset (add 0.25 of 5ht)
 * 
 * add vis1 only speed output and vis1+vis2 speed output to reward
 * 
 * check page 25 of bernd paper
 * 
 * 
 * 
 */

