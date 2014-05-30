/*#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double h=0;

double v(double xprev, double vprev, double t);
double x(double xprev, double vprev, double t);
double f(double xprev, double vnext);
double e(double t, double xprev);
double er1;
double er2;
double dz1;
double dz2;
int main()
{
	
	FILE* filename;
	filename=fopen("1.txt", "w");
	double t=0, tmax=12.56, xprev, xnext, vprev, vnext, x0=0, v0=0, k;
	printf("Enter k:\n");
	scanf("%lf", &k);
	h=0.7854/k;
	xprev=x0;
	vprev=v0;
	for(t=0;t<=(tmax+h/2);t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vprev, t);
		fprintf(filename ,"%.8lf %.4lf %.4lf %.6lf\n", t, vprev, xnext, e(t, xprev));
		if (t<=((0.7854)+h/2)&&(t>=((0.7854)-h/2)))
		{
			er1=e(t, xnext);
			dz1=x(xprev, vnext, t);
	
		}
		vprev=vnext;
		xprev=xnext;
	}
	h=h*2;
	xprev=x0;
	vprev=v0;
	for(t=0;t<=(0.7854+h/2);t=t+h)
	{
		vnext=v(xprev, vprev, t);
		xnext=x(xprev, vprev, t);
		if (t<=((0.7854)+h/2)&&(t>=((0.7854)-h/2)))
		{

			dz2=x(xprev, vnext, t);
	
		}
		vprev=vnext;
		xprev=xnext;
	}
	
	er2=dz1-dz2;
	fprintf(filename ,"%.8lf %.8lf", er1, er2);
	fclose(filename);
	system("pause");
}



double v(double xprev, double vprev, double t)
{
	return vprev+h*cos(t)-xprev*h;
}

double x(double xprev, double vnext, double t)
{
	return xprev+h*vnext;
}
double e(double t, double xprev)
{
	return 0.5*t*sin(t)-xprev;
}
*/