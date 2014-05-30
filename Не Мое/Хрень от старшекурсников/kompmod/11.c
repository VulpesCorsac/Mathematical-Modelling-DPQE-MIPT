#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>


int main ()
{
	double pi=3.141592, sqrtx, rmax;
	int year, i, n = 45, k, string;
	double srx = 0, sry=0, srxy=0, srxkv=0, kvsrx=0, a, b, x, y, summ1 = 0, summ2 = 0, r[11], xx[45];
	float harvest;
	FILE *op;
	FILE *fp;
	FILE *np;
	FILE *zp;
	op=fopen("info.txt","r");
	fp=fopen("info1.txt","w+");
	np=fopen("info2.txt","w+");
	zp=fopen("info5.txt","w+");
	srand( time( NULL ) );
	rmax = RAND_MAX;

	for (string = 0; string<=44; string++)
	{
		fscanf(op,"%d\t%f\n",&year,&harvest);
		srx = srx + year;
		sry = sry + harvest;
		srxkv = srxkv + year*year;
		srxy = srxy + harvest*year;
		xx[string] = harvest;
	}
	srx = srx / (double)45;
	sry = sry / (double)45;
	srxkv = srxkv / (double)45;
	srxy = srxy / (double)45;
	kvsrx = srx*srx;

	b = (srxy - srx*sry)/(srxkv - kvsrx);
	a = sry - b*srx;
	


sry = 0;
	for (i = 0; i <= n-1; i++)
	{
		x=i;
		xx[i]-=a+b*x;
		sry = sry + xx[i]/(double)n;
	}





	for (k = 2; k <= 10; k++)
	{
		summ1 = 0;
		summ2 = 0;
		for (i = 0; i <= n-k-1;i++)
		{
			summ1 = summ1 + (xx[i] - sry)*(xx[i+k] - sry);
			//summ2 = summ2 + (xx[i] - sry)*(xx[i] - sry);
		}
		for (i = 0; i <= n-1; i++)
		{
			summ2 = summ2 + (xx[i] - sry)*(xx[i] - sry);
		}

	
		r[k] = summ1/summ2;	
	}




//k = 1;
	
	for (x = 0; x <=44; x++)
	{
		y = a+b*x;
		fprintf(fp,"%.3f\t%.3f\n",x,y);
	//	fprintf(np,"%.3f\t%.7f\t%.3f\n",a,b,r[k]);
		//fprintf(fp,"%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t",srx,sry,srxy,srxkv,kvsrx);
		//k++;
	}
for(k = 2; k <= 10; k++)
{
	fprintf(np,"%.3f\n",r[k]);
}
fprintf(zp,"%.3f\t%.3f\n",a,b);







}
