#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double h=0,er1,er2,dz1,dz2;
double v(double x, double v, double t);
double x(double x, double v, double t);
double e(double t, double x);
double f(double x, double v, double t);
double g(double x, double v, double t);
int main()
{
	FILE* filename;
	filename=fopen("2.txt", "w");
	double t=0, tmax=12.56, xprev, xnext, vprev, vnext, k;
	printf("Enter k:\n");
	scanf("%lf", &k);
	h=1.571/k;
	xprev=0;
	vprev=0;
	for(t=0;t<=1.571;t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vprev, t);
		fprintf(filename ,"%.9lf %.9lf %.9lf %.13lf\n", t, vnext, xnext, e(t, xnext)); 
		vprev=vnext;
		xprev=xnext;
	}
	=
	xprev=0;
	vprev=0;
	for(t=0;t<=1.571;t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vprev, t);
		fprintf(filename ,"%.9lf %.9lf %.9lf %.13lf\n", t, vnext, xnext, e(t, xnext)); 
		vprev=vnext;
		xprev=xnext;
	}
	system("pause");
	fclose(filename);
}



double v(double x, double v, double t)
{
	return v+(h/2)*(g(x, v, t)+g(x+h*v,v+h*g(x,v,t), t+h));
}

double x(double x, double v, double t)
{
	return (x+(h*v)+(h*h*0.5)*g(x, v, t));
}
double g(double x, double v, double t)
{
	return (cos(t)-x);
}

double e(double t, double x)
{
	return 0.5*t*sin(t);
}