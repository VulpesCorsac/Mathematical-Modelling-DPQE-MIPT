/*                                                    */
/*                   Test for FFT                     */
/*                                                    */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <iostream>

  using namespace std;

  int const NDIM=1025; 
  complex <double>  y[NDIM],fy[NDIM];

void ffta(int nx,  complex <double>* y, int key);

void main(void)
{
	 char stnum[20];
	 int m,nx,nxm1;
	 long ir;
	 double twopi;
	 complex <double>  w0,q;
	 complex <double>  ci(0.0,1.0);

	 twopi=6.28318530717958;

	 printf("\n  nx= ");
	 gets(stnum);
	 nx=atoi(stnum);

	 nxm1=nx-1;
	 w0=exp(-ci*twopi/(double)nx);
	 q=1.01+ci*0.02;
	 cout << " q=" << q.real() << "+i*" << q.imag() <<endl;
	 cout << " q=" << real(q) << "+i*" << imag(q) <<endl;

// Fourier coefficients
	 for (m=0; m<=nxm1; m++) {
		fy[m]=(pow(q,nx)-1.)/(q*pow(w0,m)-1.)/(double)nx;
	 }
		printf("\n  fy=  \n");
	 for (m=0; m<=7; m++) {
		cout << fy[m];
	 }

// Initial vector
	 for (m=0; m<=nxm1; m++) {
		y[m]=pow(q,m);
	 }
		printf("\n  y=  \n");
	 for (m=0; m<=7; m++) {
		cout << y[m];
	 }

// Forward Fourier transform
		  ffta(nx,y,0);
	 for (m=0; m<=nxm1; m++)
		  y[m]=y[m]/(double)nx;

		printf("\n  y=  \n");
	 for (m=0; m<=7; m++) {
		cout << y[m];
	 }

// Inverse Fourier transform
		ffta(nx,y,1);

		printf("\n  y=  \n");
	 for (m=0; m<=7; m++) {
		cout << y[m];
	 }

// Repeating transforms
     for (ir=1; ir<=5000; ir++) {
	    ffta(nx,y,0);
	    for (m=0; m<=nxm1; m++)
		  y[m]=y[m]/(double)nx;
		ffta(nx,y,1);
	 }

	 cout << endl;
}

void ffta(int nx,  complex <double>* y, int key){
	 int kl,le,le2,le21,ml,ml1,n2,l2n,l2nm1,ii,ji,ic,ip,nxm1,nxm2;
	 double angle,sft,twopi;
	 complex <double> zt1,zt2,cwj;
	 complex <double> ci(0.0,1.0);

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
