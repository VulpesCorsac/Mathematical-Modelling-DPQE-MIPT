#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include<stdio.h>
using namespace std;
const double pi = 4 * atan(1.0);
const double m=1, k=1, kc=0.1;



void compute_f(const vector<double> &y_vector,vector<double> &f_vector)
{
//double B0= 1;//-0.00056856*Omega0;
//double B1=2.0*B0;
double r_x = y_vector[0],
r_y = y_vector[1],
v_x = y_vector[2],
v_y = y_vector[3],
//v_y = y_vector[4],
//v_z = y_vector[5];

f_vector[0] = v_x;
f_vector[1] = v_y;
f_vector[2] = (-k*r_x-kc*(r_x-r_y))/m;
f_vector[3] = (-kc*(r_y-r_x)-k*r_y)/m;
//f_vector[4] = (((-1)*0.25*(B1-B0)*pi)/l)*r_x*sin((pi*r_z)/l)*v_z-(B0+0.5*(B1-B0)*(1-cos((pi*r_z)/l)))*v_x;			// (((-1)*0.25*(B1-B0)*pi)/l)*r_y*sin((pi*r_z)/l) ;
//f_vector[5] = (((-1)*0.25*(B1-B0)*pi)/l)*r_y*sin((pi*r_z)/l)*v_x-(((-1)*0.25*(B1-B0)*pi)/l)*r_x*sin((pi*r_z)/l)*v_y;			// (B0+0.5*(B1-B0)*(1-cos((pi*r_z)/l))) ;
}
void RK4_step(const double h,vector<double> &y_vector)
{

int i, n = y_vector.size();
vector<double> y(n), f(n), k1(n), k2(n), k3(n), k4(n);
compute_f(y_vector, f);
for (i = 0; i < n; i++)
k1[i] = h * f[i];
for (i=0; i < n; i++)
y[i] = y_vector[i] + 0.5 * k1[i];
compute_f(y, f);
for (i = 0; i < n; i++)
k2[i] = h * f[i];
for (i=0; i < n; i++)
y[i] = y_vector[i] + 0.5 * k2[i];
compute_f(y, f);
for (i = 0; i < n; i++)
k3[i] = h * f[i];
for (i=0; i < n; i++)
y[i] = y_vector[i] + k3[i];
compute_f(y, f);
for (i = 0; i < n; i++)
k4[i] = h * f[i];
for (i = 0; i < n; i++)
y_vector[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0;


}
int main()
{


double T=1;
cout << " Enter number of periods and time-step size: ";
double periods, dt;
cin >> periods >> dt;
cout << endl;
double t = 0;
vector<double> rv(4);
rv[0] = 1;
rv[1] = 1;
rv[2] = 0;
rv[3] = 0;
//rv[4] = - Vort;
//rv[5] = Vort*tan(alpha);
ofstream data("kepler-rk4.txt");

int steps = 0, period = 0;
vector<double> rv_minus2, rv_minus1; // store solution at 2 previous steps
double t_last = t; // time at last aphelion
do
	{
		data << t << '\t';
for (int i = 0; i < 4; i++)
data << rv[i] << '\t';
data << '\n';
// update solution saved at 2 previous steps
rv_minus2 = rv_minus1;
rv_minus1 = rv;
// take one Runge-Kutta time step
RK4_step(dt, rv);


t += dt;
++steps;
	}while (t < periods * T);
cout << "\n number of RK4 steps = " << steps << '\n'
<< " data in file kepler-rk4.data" << endl;
data.close();
system("pause");
	}
/*
Bx=(((-1)*0.25*(B1-B0)*pi )/l)*y[3]*sin((pi*y[5])/l);
		By=(((-1)*0.25*(B1-B0)*pi)/l)*y[4]*sin((pi*y[5])/l);
		Bz=B0+0.5*(B1-B0)*(1-cos((pi*y[5])/l));
*/
