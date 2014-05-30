#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>


int main () 
{
	double q = 0.6, qd;
	double p, rmax, igen, H = 1, delta = 0.001, lyambda = 0.3, nh, n0 = 1000000;
	int gener,  nextnh, mh;

	FILE *op;

 	op=fopen("info.txt","w+");
 	
	gener = 3;
	nh = n0;
	nextnh = 0;
	srand( time( NULL ) );
	rmax = RAND_MAX;
	qd =  1 - (1 - q) * delta / lyambda;
	for(igen = 0; igen <= H; igen = igen + delta)
	{	
		for(mh = 1; mh <= nh; mh++)
		{
			p = rand() / rmax;
			if(p < qd)
			{
				nextnh = nextnh + 1;
			}
		}
		nh = nextnh;
		nextnh = 0;
	}
	fprintf(op,"%.6f\n",nh / n0);
	fprintf(op,"%.7f\n",qd);

	close(op);
	return 0;
}
