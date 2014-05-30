#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
double f(double t, double x, double v);
double g(double t, double x, double v);
void ffta(int nx,  double complex *y, int key);
double w0=1,z;

double mu=0.1;
double complex y[600000];
int main() {
double k1,k2,k3,k4,q1,q2,q3,q4;
double x0=-2.4,v0=0,t0=0,x1,v1,t,h=0.0001,T,tT,nxm1,z,u,s,vT;
FILE *fp,*vp,*op,*xp;
fp=fopen("info.txt","w+");
xp=fopen("info1.txt","w+");
op=fopen("info2.txt","w+");
vp=fopen("info3.txt","w+");

int n=5000000,i,mf=0,iT;
for(i=0;i<n;i++) {
fprintf(fp,"%f\t%f\n",t0,x0);
fprintf(vp,"%f\t%f\n",t0,v0);
fprintf(xp,"%f\t%f\n",v0,x0);
	k1=f(t0,x0,v0);
	q1=g(t0,x0,v0);
	k2=f(t0+h/2,x0+k1*h/2,v0+h*q1);
	q2=g(t0+h/2,x0+k1*h/2,v0+h*q1);
	k3=f(t0+h/2,x0+k2*h/2,v0+h*q2);
	q3=g(t0+h/2,x0+k2*h/2,v0+h*q2);
	k4=f(t0+h,x0+h*k3,v0+h*q3);
	q4=g(t0+h,x0+h*k3,v0+h*q3);
	v1=v0+h*(k1+2*k2+2*k3+k4)/6;
	x1=x0+h*(q1+2*q2+2*q3+q4)/6;

	

	if ((mf==1)&&(x0<0)&&(x1>0)) {
		T=h/(x1-x0)*x0+t0-tT;  
		h=T/pow(2,19); 
		printf("%f\t%.10f\n",T,T/pow(2,19)); //печатаем установившийся период
		//break;
	}
	if ((x0<0)&&(x1>0)) {
		mf++; 
		tT=t0;
		iT=i;
		vT=v0;
				
	}
	x0=x1;
	v0=v1;
	t0+=h;	
}
n=pow(2,19);
x0=0;v0=vT;t0=0;
printf("%f\n",h);
for(i=0;i<n;i++) {
	
	k1=f(t0,x0,v0);
	q1=g(t0,x0,v0);
	k2=f(t0+h/2,x0+k1*h/2,v0+h*q1);
	q2=g(t0+h/2,x0+k1*h/2,v0+h*q1);
	k3=f(t0+h/2,x0+k2*h/2,v0+h*q2);
	q3=g(t0+h/2,x0+k2*h/2,v0+h*q2);
	k4=f(t0+h,x0+h*k3,v0+h*q3);
	q4=g(t0+h,x0+h*k3,v0+h*q3);
	v1=v0+h*(k1+2*k2+2*k3+k4)/6;
	x1=x0+h*(q1+2*q2+2*q3+q4)/6;
	y[i]=x0;
	x0=x1;
	v0=v1;
	t0+=h;
}
nxm1=n-1;
// Forward Fourier transform
ffta(n,y,0);
for (i=0; i<=nxm1; i++) {
	y[i]=y[i]/n;
	z=cabs(y[i]);
if (i <= (nxm1+1)/2)
	{
		fprintf(op,"%d\t%f\n",i,z);
	}
	else 
	{
		fprintf(op,"%d\t%f\n",i-(int)nxm1,z);
	}
	
}
return 0;
}
double f(double t,double x,double v) {
return -x + mu*(1 - x*x)*v;
}
double g(double t,double x,double v) {
return v;
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
