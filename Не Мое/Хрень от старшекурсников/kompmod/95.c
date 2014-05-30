#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>


int main ()
{
	double D=0.25, x, p, pi=3.141592, sqrtx, xc, xcsr = 0, Fx, dt, x2, x2sr, r=0.5,  a, std, x0=0, tzsr, tz,  t0=0, rmax;
	int st = 100, n = 10000, tprint, nprint, tcur, ncur, t;
	double  memor[n][st];
	FILE *op;
	x2 = 0;
	op=fopen("info.txt","w+");
	srand( time( NULL ) );
	rmax = RAND_MAX;
	std = st;
	dt=1/std;
	a=sqrt(dt*D*2);
	ncur = 0;
	for (ncur = 0; ncur < n; ncur++)
	{	
		x = 0;
		t = 0;
		for (t=0; t < st; t++)
		{   
			p = rand() / rmax;
			if (p <= 0.5)
			{
				x-=a;
			}
			else if (p > 0.5)
			{
				x+=a;
			}
			memor[ncur][t] = x;
		}
	}
	for (nprint = 0; nprint < n; nprint++)
	{
		xc = 0;
		tz=0;
		for (tprint = 0; tprint < st; tprint++)
		{
			x2+=memor[nprint][tprint]*memor[nprint][tprint]/n/st;
			if (xc < fabs(memor[nprint][tprint]))
			{
				xc = fabs(memor[nprint][tprint]);
			}
			if (fabs(memor[nprint][tprint]) > r)
			{
				tz++;
			}
			
			//fprintf(op,"%.1f\t",memor[nprint][tprint]);
		}
		xcsr+=fabs(xc)/n;
		tzsr+=tz/n/st;
		//fprintf(op,"\n");
		
	}
	fprintf(op,"M(||x||^2) = %.2f\nM(||x||c)  = %.2f\nM(F[x])    = %.2f\n",x2,xcsr,tzsr);
}
