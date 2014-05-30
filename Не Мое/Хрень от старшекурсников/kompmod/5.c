#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>
#include <complex.h>

void ffta(int nx,  double complex *s, int key);

int main ()
{
	double b = 0.1, D=0.25, p, pi=3.141592, sqrtx, xc, xcsr = 0, Fx, dt, SlVel1, SlVel2, x2, x2sr, r=0.5,  a, std, x0=0, tzsr, tz,  t0=0, rmax,  w0 = 1, w = sqrt(w0*w0 - b*b);
	int st = 100, n, tprint, nprint, tcur, ncur, t, M = 1024, i,ki, l;
	double  SABS, delta = 0.2, x[M][2], 

	K[4] = {exp(-b*delta)*(cos(w*delta) + b / w *sin(w*delta)), exp(-b*delta)*sin(w*delta) / w, exp(-b*delta)*(-w0*w0)*sin(w*delta)/w, exp(-b*delta)*(cos(w*delta) - b * sin(w*delta) / w)}, G[2] = {0,1}, N[M], C[2] = {1,0};
	double complex SCO[M];
	double SRE[M];
	FILE *op;
	FILE *fp;
	op=fopen("info.txt","w+");
	fp=fopen("info1.txt","w+");
	srand( time( NULL ) );
	rmax = RAND_MAX;
	
SCO[0] = 0; // signal out
x[0][0] = 0;
x[0][1] = 0;
SlVel1 = rand() / rmax;
SlVel2 = rand() / rmax;
N[0] = sqrt(-2*log(SlVel1))*cos(2*pi*SlVel2);
	for(n = 1; n < M; n++)
	{
		SlVel1 = rand() / rmax;
		SlVel2 = rand() / rmax;
		N[n] = sqrt(-2*log(SlVel1))*cos(2*pi*SlVel2);	
		
		x[n][0] = K[0]*x[n-1][0] + K[1]*x[n-1][1] + G[0]*N[n-1];
		x[n][1] = K[2]*x[n-1][0] + K[3]*x[n-1][1] + G[1]*N[n-1];
		SCO[n] = C[0]*x[n][0] + C[1]*x[n][1];
		SRE[n] = C[0]*x[n][0] + C[1]*x[n][1];

		fprintf(op,"%.2f\n",SRE[n]);
	}

for (l=0; l<=M-1; l++)
{
l=l*(-1)^l;

ffta(M,SCO,0);

//for (i=0; i<=M-1; i++) 
//{
	SCO[l]=SCO[l]/(M);
	SABS=cabs(SCO[l]);



fprintf(fp,"%d\t%.2f\n",(-1)*M/2+i,SABS);
//}
}
}

void ffta(int nx,  double complex *y, int key){
	 int kl,le,le2,le21,ml,ml1,n2,l2n,l2nm1,ii,ji,ic,ip,nxm1,nxm2;
	 double angle,sft,twopi;
	 double complex zt1,zt2,cwj;
	 double complex ci=I;

	 twopi=6.28318530717958;
	 nxm1=nx-1;

		ii=0;
		ji=1;
	 while (ji < nx) {
		ii+=1;
		ji*=2;
	 }
		l2n=ii;
		l2nm1=l2n-1;

		n2=nx/2;

	 if (key == 0)
		sft=-1.;
	 else
		sft=1.;
	 for (kl = 0; kl <= l2nm1; kl++) {
		  le = 1 << (l2n-kl);
		  le2=le/2;
		  le21=le2-1;
		  ml=nx/le;
		  ml1=ml-1;
		for (ji = 0; ji <= le21; ji++) {
			 angle=twopi*(double)ml*(double)ji/(double)nx;
			 cwj = cos(angle) + ci*sft*sin(angle);
		  for (ic = 0; ic <= ml1; ic++) {
			 ii=ji+ic*le;
			 ip=ii+le2;
			 zt1=y[ii];
			 zt2=y[ip];
			 y[ii]=zt1+zt2;
			 y[ip]=(zt1-zt2)*cwj;
		  }
		}
	 }

		nxm2=nx-2;
		ji=0;
	 for (ii = 1; ii <= nxm2; ii++) {
		  ip = n2;
		while (ip < ji+1) {
		  ji=ji-ip;
		  ip=ip/2;
		}
		  ji=ji+ip;
		if (ii < ji) {
		  cwj=y[ji];
		  y[ji]=y[ii];
		  y[ii]=cwj;
		}
	 }

}

