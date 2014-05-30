#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
	{	                         
		FILE *fOut;
		fOut = fopen("pro.txt","w");
		int i,N;
		long double h,a[10000],b[10000],c[10000],f0=0,f,cSH[10000],fSH[10000],ut[10000],u[10000];
 
		printf("Input h: ");
		scanf("%lf", &h);
		N=1./h;
		
		a[0]=0;
		b[0]=0;
		c[0]=1;
		c[N]=1;
		a[N]=0;
		b[N]=0;
  fSH[0]=f0;
  f0=0.5*h*h;
  fSH[1]=-(2*h*h*h);
  fSH[N]=0;
  cSH[0]=1;
  cSH[1]=2+h*h;
  cSH[N]=1;
  u[N]=-1;
  u[0]=0;
  for(i=1; i<N; i++)
  {
	  a[i]=-1;
	  b[i]=-1;
	  c[i]=2+h*h;
  }
  
  for(i=1;i<N;i++)
  {
        f=-(2*h*h*i*h);
        cSH[i]=c[i]-a[i]*b[i-1]/cSH[i-1];
        fSH[i]=f-a[i]*fSH[i-1]/cSH[i-1];
  }

  for(i=N-1;i>=0;i--)
  {
        u[i]=fSH[i]-b[i]*u[i+1]/cSH[i];
  }

  for(i=0;i<=N;i++)
  {
        ut[i]=sinh(i*h)/sinh(1.0) - 2*i*h;
        
  }
  		
		for(i=0;i<=N;i++)
		{
		fprintf(fOut,"%.10Lf    %.10Lf    %.10Lf    %.10Lf\n",i*h  , u[i], ut[i] , (u[i]-ut[i]));
		}

		system("pause");
	fclose(fOut);

	}