#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>


int main ()
{
	double D=0.25, x, p, p1, p2,  pi=3.141592, sqrtx, xc, xcsr = 0, Fx, dt = 1, ei, T = 16, k, t = 0,  N = 10000, us, x2, x2sr, r=0.5,  a, std, x0=0, tzsr, tz,  t0=0, B = 0.2, rmax, umax, ucur;
	int st = 100, tprint, i, iter, j, nprint, tcur, ncur, n, ny = 1, M = 8, m, l = 5, C = 1, i2;
	double fi, Um[M], u1[10000], u2[10000], u[10000], usht[l];
	FILE *op;
	FILE *fp;
	FILE *np;
	op=fopen("info.txt","w+");
	fp=fopen("info1.txt","w+");
	np=fopen("info2.txt","w+");
	srand( time( NULL ) );
	rmax = RAND_MAX;
	dt = T / N;
	k = (l - 1)/2;
	
	
	for(m = 0; m < M; m++)
	{
		p = rand() / rmax * T;
		Um[m] = p;
	}
	
	n = 0;

	for(t = 0; t < T; t = t + dt)
	{
		u[n] = 0;
		fi = sin(2*ny*pi*t);
		for(m = 0; m < M; m++)
		{

			if ((t <= Um[m])&&(t+dt >= Um[m]))
			{
				p1 = rand() / rmax;
				p2 = rand() / rmax;
				u[n] = C * sqrt(-2*log(p1))*cos(2*pi*p2) ;
			}
		}
		p1 = rand() / rmax;
		p2 = rand() / rmax;
		ei = B * sqrt(-2*log(p1))*cos(2*pi*p2);
		u[n] = -u[n] + fi + ei;
		fprintf(op,"%.3f\n",u[n]);
		n++;
	}
n = k;

for (iter = 0; iter < 1; iter++)
{
	for(n = k; n <= N - k; n++)
	{	
		us = 0;
		for(i = n - k; i < n + k; i++)
		{
			us+=u[i];
		}
		
		u1[n] = us/5;		

		fprintf(fp,"%.3f\n",u1[n]);
	}
}
n = k;
for (iter = 0; iter < 2; iter++)
{
	for(n = k; n <= N - k; n++)
	{	
		i2=0;
		for(i = n-k; i<n+k;i++)
		{
			usht[i2]=u[i];
			i2++;
		}

j=0;
		while(j!=1)
		{	
			i2=1;
			j = 1;
			for(i2 = 1; i2 <= l; i2++)
			{
				
			
				if(usht[i2-1] > usht[i2])
				{
					ucur = usht[i2-1];
					usht[i2-1] = usht[i2];
					usht[i2] = ucur;
					j = 0;
				}
				
			}
			
		}	
		u2[n]=usht[(l-1)/2];
		fprintf(np,"%.3f\n",u2[n]);
	}
	
}
}
