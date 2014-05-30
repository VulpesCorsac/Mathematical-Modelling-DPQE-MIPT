#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double b;
double h=0;
double v(double x, double v, double t);
double x(double x, double v, double t);
//double vcor(double x, double v, double t);
//double xcor(double x, double v, double t);
double e(double t, double x);
double f(double x, double v, double t);
double g(double x, double v, double t);
double er1=0;
double er2=0;
double dz1=0;
double dz2=0;
int main()
{
	FILE* filename;
	filename=fopen("2.txt", "w");
	double t=0, tmax=12.56, xprev, xnext, vprev, vnext, x0=0, v0=0, k;
	printf("Enter k:\n");
	scanf("%lf", &k);
	h=0.7854/k;
	xprev=x0;
	vprev=v0;
	for(t=h;t<=tmax;t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vprev, t);
		fprintf(filename ,"%.9lf %.9lf %.9lf %.13lf\n", t, vnext, xnext, e(t, xnext)); 
		if (t<=((0.7854)+h/8)&&(t>=((0.7854)-h/8)))
		
		{
		//	er1=e(t, xprev);
		//	dz1=xnext;
			//h=2*h;
			//dz2=x(xprev, vprev, t);
			//h=h/2;
	       // er2=(dz1-dz2)/3;
		}
		vprev=vnext;
		xprev=xnext;
	}
	h=h*2;
	xprev=x0;
	vprev=v0;
	for (t=h;t<=0.7854+h;t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vnext, t); 
		if (t<=((0.7854)+h/8)&&(t>=((0.7854)-h/8)))	
		{

			//dz2=xnext;
			//er2=(dz1-dz2)/3;
		}
		vprev=vnext;
		xprev=xnext;
	}
	
	//fprintf(filename ,"%.19lf %.19lf", er1, er2);
	printf("%.19lf %.19lf", er1, er2);
	system("pause");
	fclose(filename);
}



double v(double x, double v, double t)
{
	return v+(h/2)*(g(x, v, t-h)+g(x+h*v,v+h*g(x,v,t-h), t));
}

double x(double x, double v, double t)
{
	return (x+(h*v)+(h*h/2)*g(x, v, t-h));
}/*
double vw(double x, double v, double t)
{
	return v+h*g(x, v, t-h);
}

double xw(double x, double v, double t)
{
	return x+h*v;
} 

double v(double x, double v, double t)
{
	return v+0.5*h*(g(x, v, t)+g(xw(x, v, t), vw(x, v, t), t+h));
}

double x(double x, double v, double t)
{
	return x+0.5*h*(v+vw(x, v, t));
}
*/
/*double f(double x, double v, double t)
{
	return v;
}*/
double g(double x, double v, double t)
{
	return (cos(t)-x);
}

double e(double t, double x)
{
	return 0.5*t*sin(t)-x;
}