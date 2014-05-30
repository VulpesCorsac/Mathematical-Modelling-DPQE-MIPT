#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double h=0;

double x(double xp,  double tp);

double e(double t, double x);

double f(double x,  double t);


int main()
{
	FILE* filename;
	filename=fopen("1.txt", "w");
	double t=0, tmax=0.9, xprev, xnext, x0;
	printf("Enter h:\n");
	scanf("%lf", &h);
	printf("Enter x0:\n");
	scanf("%lf", &x0);
	xprev=x0;
	for(;t<=tmax;t=t+h)
	{
		xnext=x(xprev, t);
		fprintf(filename ,"%.7lf %.7lf %.7lf\n", t, xnext, e(t, xnext)); 
		xprev=xnext;
	}
	fclose(filename);
	system("pause");
}



double x(double xp, double tp)
{
	return xp+h*f(xp,tp);
}

double f(double x, double t)
{
	return x*x;
}

double e(double t, double x)
{
	return ((-1)/(t-1))-x;
}