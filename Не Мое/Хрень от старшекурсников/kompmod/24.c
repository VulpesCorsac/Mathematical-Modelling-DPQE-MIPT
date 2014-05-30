#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>
const int N = 5000;
const double pi = 3.141592;
int main ()
{
	double rmax, p, u, pu, a[N];
	int x=0, n=0, i=0, E=10000, exp=0, srzero=0, overzero=0, flag;
	FILE *op;
	FILE *fp;
	FILE *np;
	op=fopen("info.txt","w+");
	fp=fopen("info1.txt","w+");
	np=fopen("info2.txt","w+");
	

	srand( time( NULL ) );
	rmax = RAND_MAX;
	for (flag=0; flag<N; flag++)
	{
		a[flag]=0;
	}
	for (exp=0; exp<E; exp++)
	{
		n=0;
		overzero=0;
		x=0;
		for (n=0;n<N; n++)
		{
			p = rand() / rmax;		
			if (p<=0.5)
			{
				x++;
			}
			else 
			{
				x--;
			}
			if (x==0)
			{
				i++;
			}
			if (x>0)
			{
				overzero++;
			}
		}
		a[overzero]++;
		
	}
	for (flag=0; flag<N; flag++)
	{
		fprintf(fp,"%d\t%.4f\n",flag,a[flag]/4.4);	
	}
u=0.01;
	for (u=0.001; u<0.999; u=u+0.001)
	{	
		pu=1/(pi*sqrt(u*(1-u)));
		fprintf(np,"%.4f\t%.4f\n",u*N,pu);
	}
	srzero=i/E;
	fprintf(op,"%d\n",srzero);
	close(op);
	close(fp);
}
