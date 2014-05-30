#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double l=10000,d=1000, lambda=1,xscreen, xsource, h=0.1, pi=3,1415926535, intensityonscreen;
double intensity(double a);
int main()
{
	FILE* filename;
	filename=fopen("2.txt", "w");
	for(xscreen=0;xscreen<=10000;xscreen=xscreen+h)
	{
	for(xsource=0;xsource<=d;xsource=xsource+h)
	{
		

	}
		fprintf(filename ,"%.9lf %.2lf\n", intensityonscreen, xscreen); 
	}
	system("pause");
	fclose(filename);
}

double intensity(double a)
{
	return ;
}
