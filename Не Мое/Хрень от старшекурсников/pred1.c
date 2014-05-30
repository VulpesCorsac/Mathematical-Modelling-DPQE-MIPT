#include <stdio.h>
#include <math.h>

int main()
{	
        FILE *fOut;

	//
	fOut = fopen("pred.out", "w");
	long double lamda = 1;
	long double omega0 = 0.5;
	long double x0 = 0;
	long double v0 = 1;
	long double tmax = 3 / lamda;
	
	
	long double f(long double v, long double x)
	{
		return - (2 * lamda * v + omega0 * omega0 * x);
	}
	
	long double step = 0.001; 
	long double omega = powl(lamda * lamda - omega0 * omega0, 0.5);
	long double x = x0;  //x(t)методом Эйлера
	long double v = v0;  //v(t)методом Эйлера
	long double time = 0;
	long double xAn = x0;
	long double X1 = 0;
	long double X = x0;  //х(t) методом предитор-корректор
        long double V = v0;  //v(t) методом предитор-корректор
        long double xend ;		
	long double Xend ;
	long double dstep = 2 * step;
	//long double XRynge;*/
  for(time = 0; time < tmax + step; time += step)
  {
	  
    xend = x;
    Xend = X;
	  xAn = v0 / omega * expl (- lamda * time) * sinh (omega * time) ; //аналитическое решение
	  fprintf(fOut, "%.3Lf    %.10Lf %.10Lf    %.10Lf  %.10Lf    %.10Lf  %.10Lf     %.10Lf\n", time, x, v, xAn, xAn - x, X, V, xAn - X); 
	  X1 = X;
	  X += step * V + step * step / 2 * f(V, X);
	  V += step / 2 * (f(V, X1) + f(V + step * f(V, X1), X1 + step * V));
	  v += step * f(v,x);
	  x += step * v;
  }
 
    
     V = v0;
     v = v0;
     x = x0;
     X = x0;
  for(time = 0; time < tmax; time += dstep)
  {
         X1 = X;
         X += dstep * V + dstep * dstep / 2 * f(V, X);
         V += dstep / 2 * (f(V, X1) + f(V + dstep * f(V, X1), X1 + dstep * V));
	 v += dstep * f(v,x);
	 x += dstep * v;
  }
  
  printf("%.10Lf  %.10Lf\n",xend - x ,(Xend - X) / 3 );
    return 0;
  }