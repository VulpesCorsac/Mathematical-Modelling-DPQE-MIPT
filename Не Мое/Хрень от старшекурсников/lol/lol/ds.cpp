#include <iostream>
#include <cmath.h>
#define h 0.01
#define k 3140
#define s 5000
double G=0.8,O=1,T=31.4;
using namespace std;
int main(int i)
{   
	double V[k]={0},F[s]={0},X[s]={0};
	double  outX[s]={0},outV[s]={0},e[s]={0},t=0;
			X[0];
			V[0];	
			for(i=0;i<k;i++,t<T) 
				{
					V[i]=V[i]+h*cos(G*t)-O*O*X[i];
					X[i]=X[i]+h*V[i+1];
			//	V[i]=V[i]+0.5*h*(cos(G*t)-O*O*X[i]+0.5*h*(cos(G*(t+h)-O*O*(X[i]+h*V[i]))));
				//	X[i]=X[i]+0.5*h*V[i]+0.5*h*h*F[i];
					outX[i]=X[i];
					outV[i]=V[i];
					t=t+h;
					cout<<V[i];
				}
		
						t=0;
					for( i=0;i<=k;i++)
						{
								e[i]=(2.0/(O*O-G*G)*sin(0.5*(O+G)*t)*sin(0.5*(O-G)*t)-outX[i]);
								t=t+h;
						} 
	t=0;
	FILE *pFile1;
	pFile1=fopen ("outX(t).txt","w");
					for (i=0;i<=k;i++)
						{
							fprintf (pFile1, "%f\t%f\n",outX[i],t);
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
/*int counter()
{
	double G=0.8,O=1;
	double T=31.4,V0=0,V,f=0,X,X0=0,t=0;
	//double  outX[s]={0},outV[s]={0},e[s]={0};
	while (t<T)
	{
		i=0;
		V=0;
		X=0;
		for(i=0;i<=k;i++) 
		{
			f=cos(G*t)-O*O*X;
			V=V+h*f;
			X=X+h*V;
			outV[i]=V;
			outX[i]=X;
			
			t=t+h;
			cout<<X;
	}
	t=0;
	for( i=0;i<=k;i++)
	{
		e[i]=(2.0/(O*O-G*G)*sin(0.5*(O+G)*t)*sin(0.5*(O-G)*t)-outX[i]);
		t=t+h;
		cout<<e[i];
	} 
	t=0;

}
	return 0;
}*/