#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main()
{
	srand (10);
	
	double  w, x0, x;
	int proletevshie = 0;
	bool live;

	int N = 10000000;//
	double h1 = 0.4, h2 = 0.5, q1 = 0.5, q2 = 0.6, l1 = 0.2, l2 = 0.3;//

	for (int n = 1; n <= N; n++)
	{
		x = 0;
		live = true;

		while (x < h1+h2 && live == true)
		{
			w = rand()/double(32767);

			if (x > h1)
				x+= -l2*log(1-w);
			else
			{
				x0 = h1 - x;
				if (w <= 1 - exp(-x0/l1))
					x += -l1*log(1 - w);
				else
					x+= x0 - l2*(log(1 - w) + x0/l1);
			}
			
			w = rand()/double(32767);
			
			//умер или нет
			if (x < h1 && w < 1-q1 || x > h1 && x < h1 + h2 && w < 1 - q2)
				live = false;
		}
		
		if (live)
			proletevshie++;
	}

	cout << proletevshie/double(N);

	return 0;
}