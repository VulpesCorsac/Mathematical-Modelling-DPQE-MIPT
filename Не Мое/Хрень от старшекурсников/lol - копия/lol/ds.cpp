#include <iostream>
#include <math.h>
//#include <conio.h>
#define h 0.01
#define k 3140
using namespace std;
int main(int i)
{   
	double G=0.8,O=1;
	double T=31.4;
	//double h=0.1;
	double cX[5000]={0}, pX[5000]={0}, cY[5000]={0}, pY[5000]={0}, cF[5000]={0}, pF[5000]={0},OUT[5000]={0},e[5000]={0};
	double t=0;
	while (t<T)
	{
		i=0;
		for(i=0,i=0;i<=k;i++) 
		{
			cX[0]=0;
			cY[0]=0;
			OUT[0]=0;
			//cF[0]=1;
			pF[i]=cos(G*t)- O*O*pX[i]; 
			pY[i+1]=cY[i] +h*pF[i];
			pX[i+1]=cX[i] +h*pY[i+1];
			pF[i]=cos(G*t)-O*O*cX[i];
			t=t+h;
			OUT[i+1]=pX[i+1];


			/*pF[i]=cos(G*t)- O*O*pX[i]; 
			pY[i+1]=cY[i] +h*pF[i];
			pX[i+1]=cX[i] +h*cY[i];
			pF[i]=cos(G*t)-O*O*cX[i];

			t=t+h;

			cF[i+1]=cos(G*t)-O*O*pX[i+1];
			cY[i+1]=cY[i]+0.5*h*(pF[i]+cF[i+1]);
			cX[i+1]=cX[i]+0.5*h*(cY[i]+pY[i+1]);
			
			OUT[i+1]=cX[i+1];*/
		}
	}

	t=0;

	for( i=0;i<=k;i++)
	{
		e[i]=(2.0/(O*O-G*G)*sin(0.5*(O+G)*t)*sin(0.5*(O-G)*t)-OUT[i]);
		t=t+h;
	}
	t=0;
	FILE *pFile1;
	pFile1=fopen ("outX(t).txt","w");
	for (i=0;i<=k;i++)
	{
		fprintf (pFile1, "%f\t%f\n",OUT[i],t);
		t=t+h;
	}
	fclose (pFile1);

	t=0;

	FILE *pFile2;
	pFile2=fopen ("outE(t).txt","w");
	for(i=0;i<=k;i++)
	{
		fprintf (pFile2, "%f\t%f\n",e[i],t);
		t=t+h;
	}
	fclose (pFile2);
	


	system("pause");
	return 0;
	
}

