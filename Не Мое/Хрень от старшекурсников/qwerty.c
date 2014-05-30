#include <stdio.h>
#include <math.h>


#define l 1
#define	N 1000
#define	A 0
#define	B -1
#define	alfa 1


enum ERRORS
{
	OK = 0
	,ERROR = 1
};

long double secondDerivative(long double x)
{
	return  2 * x;
}

int main()
{
	FILE *fout = fopen("qwerty.out", "w");
	
	long double h = l;
	h /= N;
	int numberOfPoints = N;
	
	long double systMatr[3][4][N+1] = {{{0}}};
	int calculationNumber;
	int cellNumber;
	
	
	for(calculationNumber = 0; calculationNumber < 3; ++calculationNumber)
	{
		systMatr[calculationNumber][3][0] = A;
		systMatr[calculationNumber][1][0] = 1;
		systMatr[calculationNumber][3][numberOfPoints] = B;
		systMatr[calculationNumber][1][numberOfPoints] = 1;
		
		for(cellNumber = 1; cellNumber < numberOfPoints; ++cellNumber)
		{
			systMatr[calculationNumber][0][cellNumber] = 1;
			systMatr[calculationNumber][1][cellNumber] = -(2 + h * h);
			systMatr[calculationNumber][2][cellNumber] = 1;
			systMatr[calculationNumber][3][cellNumber] = h * h * secondDerivative(cellNumber * h);
		}
		
		
		for(cellNumber = 1; cellNumber < numberOfPoints; ++cellNumber)
		{
			systMatr[calculationNumber][3][cellNumber] -= systMatr[calculationNumber][3][cellNumber - 1] * systMatr[calculationNumber][0][cellNumber] / systMatr[calculationNumber][1][cellNumber - 1];
			systMatr[calculationNumber][1][cellNumber] -= systMatr[calculationNumber][2][cellNumber - 1] * systMatr[calculationNumber][0][cellNumber] / systMatr[calculationNumber][1][cellNumber - 1];
			systMatr[calculationNumber][0][cellNumber] = 0;
			
			systMatr[calculationNumber][3][numberOfPoints - cellNumber] -= systMatr[calculationNumber][3][numberOfPoints - cellNumber + 1] * systMatr[calculationNumber][2][numberOfPoints - cellNumber] / systMatr[calculationNumber][1][numberOfPoints - cellNumber + 1];
			systMatr[calculationNumber][1][numberOfPoints - cellNumber] -= systMatr[calculationNumber][0][numberOfPoints - cellNumber + 1] * systMatr[calculationNumber][2][numberOfPoints - cellNumber] / systMatr[calculationNumber][1][numberOfPoints - cellNumber + 1];
			systMatr[calculationNumber][2][numberOfPoints - cellNumber] = 0;
		}
		
		
		for(cellNumber = 0; cellNumber < numberOfPoints + 1; ++cellNumber)
		{
			systMatr[calculationNumber][3][cellNumber] /= systMatr[calculationNumber][1][cellNumber];
			systMatr[calculationNumber][1][cellNumber] = 1;
			
		}
	numberOfPoints /= 2;
	h *= 2;
	}
	h /= 8;
	for(cellNumber = 0; cellNumber < N + 1; ++cellNumber)
	{
		fprintf(fout, "%Lf %Lf %Lf %Lf %.15Lf %.15Lf\n", h * cellNumber, systMatr[0][0][cellNumber], systMatr[0][1][cellNumber], systMatr[0][2][cellNumber],systMatr[0][3][cellNumber], systMatr[0][3][cellNumber] - ( sinhl(cellNumber * h) / sinhl(1) - 2 * cellNumber * h) );
	}
	long double orderOfConvergence = logl((systMatr[1][3][N / 2 - 2] - systMatr[2][3][N / 4 - 1]) / (systMatr[0][3][N - 4] - systMatr[1][3][N / 2 - 2])) / logl(2);
	printf("%Lf\n", orderOfConvergence);
	close(fout);
	return OK;
}