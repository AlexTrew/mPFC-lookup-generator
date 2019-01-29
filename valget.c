#include "stdio.h"
#include "math.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include <time.h>
#include "unistd.h"

double 
lookup(double _5ht,double x, int type)
{
    switch(type)
    {
        case 1: //control
            return (1-exp(-pow(x/_5ht,_5ht)))*_5ht;
            
        case 2://nutt
            return ((1-exp(-pow(x/_5ht,_5ht)))*(_5ht+1));
        
        case 3: //drn_supression + ssri
            return (1-exp(-pow(x/(_5ht+1),(_5ht+1))))*(_5ht+0.5);
            
                    
    }
    
}
    
    
int 
main(int argc, char** argv)
{
    printf("case %d: waitspeed: %lf, movespeed %f\n", atoi(argv[2]), 100*lookup(atof(argv[1]), 1.0, atoi(argv[2])), 100 *lookup(atof(argv[1]), 2.0, atoi(argv[2])));
    
    return 0;
}
