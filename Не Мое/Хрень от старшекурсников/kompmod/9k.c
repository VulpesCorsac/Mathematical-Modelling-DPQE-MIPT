#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>
#include <complex.h>

void ffta(int nx,  double complex *s, int key);

int main ()
{
	double D=0.25, p, pi=3.141592, sqrtx, xc, xcsr = 0, Fx, dt, p1, p2, x2, x2sr, std, x0=0, tzsr, tz,  t0=0, rmax;
	int st = 100, n, tprint, nprint, tcur, ncur, zadanie = 0;
	double  z, delta = 0.2, G[2] = {0,1}, C[2] = {1,0};
	double nt[20000];
	double M=1000, b = 1, Nt, t,gamma,r,fi,a,d;
	int i,j,Inv;
	FILE *op;
	FILE *fp;
	op=fopen("info.txt","w+");
	fp=fopen("info1.txt","w+");
	srand( time( NULL ) );
	rmax = RAND_MAX;
 	t=0;
        Inv=0; 
        i = 0;
        j = 0;
        a = 0;
        d = 0; 
	
 	for (i = 0; i <= 1000; i++)
               {
                  // t = random.Next(0, 1000);
                   
		   p1 = rand() / rmax;
		   p2 = rand() / rmax;
                   Nt = sqrt(-2*log(p1))*cos(2*pi*p2);
if(zadanie == 1)
{
                   nt[i] = b * i / M + Nt;
}
else 
{
nt[i] = b*sin(8 * pi * i / M )+ Nt;
}

fprintf(op,"%d\t%.3f\n", i,nt[i]);

                 //  chart1.Series[0].Points.AddXY(i, nt[i]);                
               }
	Inv = 0;
               for (i = 0; i <= 1000; i++)
               {
                   for (j = i; j < 1000; j++)
                   {
                       if (nt[j] > nt[i])
                       {
                           Inv++;
                       }
                   }
               }    	


   gamma = (1 - 4 * Inv / (M * (M - 1))) / sqrt(2 * (2 * M + 5) / (9 * M * (M - 1)));
printf("%f\n",gamma);

	if (gamma <= 1.96 && gamma >= -1.96)
               {
                    printf("Выполнено\n");

                   a++;

               }
	else
               {
                    printf("Не выполнено\n");

                   d++;

               }   





}

