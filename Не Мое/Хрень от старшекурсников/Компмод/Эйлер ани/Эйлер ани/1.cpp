#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double h=0,w0=1;

double v(double xp, double vp, double tp);
double x(double xp, double vp, double tp);

double e(double t, double x);

double f(double x, double v, double t);
double g(double x, double v, double t);

int main()
{
	FILE* filename;
	filename=fopen("1.txt", "w");
	double t=0, tmax=1, xprev, xnext, vprev, vnext, x0, v0;
	printf("Enter tmax:\n");
	scanf("%lf", &tmax);
	printf("Enter h:\n");
	scanf("%lf", &h);
	printf("Enter 0<x0<pi (rad):\n");
	scanf("%lf", &x0);
	printf("Enter v0:\n");
	scanf("%lf", &v0);
	xprev=x0;
	vprev=v0;
	for(;t<=(tmax+h/4);t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vprev, t);
		fprintf(filename ,"%.7lf %.7lf %.7lf\n", t, vnext, xnext); 
		vprev=vnext;
		xprev=xnext;
	}
	fclose(filename);
	system("pause");
}


double v(double xp, double vp, double tp)
{
	return vp+h*g(xp,vp,tp);
}

double x(double xp, double vp, double tp)
{
	return xp+h*f(xp,vp,tp);
}

double f(double x, double v, double t)
{
	return v;
}
double g(double x, double v, double t)
{
	return -pow(w0,2)*sin(x);
}
