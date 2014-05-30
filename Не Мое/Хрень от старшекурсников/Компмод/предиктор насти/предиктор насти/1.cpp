#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double h=0;


double x(double xp, double tp);

double xcor(double xp,  double tp);

double e(double t, double x);

double f(double x,  double t);
double g(double x,  double t);

int main()
{
	FILE* filename;
	filename=fopen("2.txt", "w");
	double t=0, tmax=0.9, xprev, xnext,  x0;
	printf("Enter h:\n");
	scanf("%lf", &h);
	printf("Enter x0:\n");
	scanf("%lf", &x0);

	xprev=x0;

	for(;t<=(tmax-h/4);t=t+h)
	{
		
		xnext=xcor(xprev,  t);
		fprintf(filename ,"%.7lf %.7lf %.7lf\n", t+h, xnext, e(t+h, xnext)); 
		
		xprev=xnext;
	}

	system("pause");
	fclose(filename);
}



double x(double xp, double tp)
{
	return xp+h*f(xp,tp);
}

double xcor(double xp, double tp)
{
	return xp+0.5*h*(f(xp, tp)+f(x(xp, tp),  tp+h));
}


double g(double x, double t)
{
	return x*x;
}

double e(double t, double x)
{
	return (-1)/(x-1);
}