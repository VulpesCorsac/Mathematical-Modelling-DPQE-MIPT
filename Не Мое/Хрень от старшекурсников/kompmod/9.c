#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>

int main () 
{
	double pk0 = 0.4, pk1 = 0.3, pk2 = 0.15, pk3 = 0.1, pk4 = 0.05;
	double pu0 = 0.45, pu1 = 0.3, pu2 = 0.1, pu3 = 0.1, pu4 = 0.05;
	double pe0 = 0.475, pe1 = 0.3, pe2 = 0.1, pe3 = 0.1, pe4 = 0.025, sqsnk = 0 ;
	double p, rmax, sk = 0, su = 0, se = 0, statk, statu, state, gamma = 1.96, survk, surve, survu, theorsurvk, theorsurve, theorsurvu;
	long n0 = 50, years = 600, swap = 25, gener, nk, nu, ne, nextnk, nextnu, nextne, ipokol, mk, mu, me, i, k = 10000, deathk = 0, deathu = 0, deathe = 0;
	long snk = 0, snu = 0, sne = 0, sqsnu = 0, sqsne = 0, snksq = 0, snusq = 0, snesq = 0;

	FILE *fp,*op;

 	op=fopen("info.txt","w+");

	gener = years / swap;
	rmax = RAND_MAX;
	
	//srand( time( NULL ) );
for(i = 0; i <= k; i++)
{
	nk = n0;
	nu = n0;
	ne = n0;
	nextnk = 0;
	nextnu = 0;
	nextne = 0;
	for(ipokol = 1; ipokol <= gener; ipokol++)
	{	
		for(mk = 1; mk <= nk; mk++) 
		{
			p = rand() / rmax;
			if(p < pk1)
			{
				nextnk = nextnk + 1;
			}
			else if(p < (pk1 + pk2))
			{
				nextnk = nextnk + 2;
			}
			else if(p < (pk1 + pk2 + pk3))
			{
				nextnk = nextnk + 3;
			}
			else if(p < (pk1 + pk2 + pk3 + pk4))
			{
				nextnk = nextnk + 4;
			}
		}
		for(mu = 1; mu <= nu; mu++) 
		{
			p = rand() / rmax;
			if(p < pu1)
			{
				nextnu = nextnu + 1;
			}
			else if(p < (pu1 + pu2))
			{
				nextnu = nextnu + 2;
			}
			else if(p < (pu1 + pu2 + pu3))
			{
				nextnu = nextnu + 3;
			}
			else if(p < (pu1 + pu2 + pu3 + pu4))
			{
				nextnu = nextnu + 4;
			}
		}
		for(me = 1; me <= ne; me++) 
		{
			p = rand() / rmax;
			if(p < pe1)
			{
				nextne = nextne + 1;
			}
			else if(p < (pe1 + pe2))
			{
				nextne = nextne + 2;
			}
			else if(p < (pe1 + pe2 + pe3))
			{
				nextne = nextne + 3;
			}
			else if(p < (pe1 + pe2 + pe3 + pe4))
			{
				nextne = nextne + 4;
			}
		}
		nk = nextnk;
		nu = nextnu;
		ne = nextne;
		nextnk = 0;
		nextnu = 0;
		nextne = 0;
	}
	
sqsnk = sqsnk + nk * nk;
sqsnu = sqsnu + nu * nu;
sqsne = sqsne + ne * ne;
snk = snk + nk;
snu = snu + nu;
sne = sne + ne;
if(nk == 0)
{
	deathk++;
}
if(ne == 0)
{
	deathe++;
}
if(nu == 0)
{
	deathu++;
}
}
snk = snk / k;
snu = snu / k;
sne = sne / k;

sqsnk = sqsnk / k;
sqsnu = sqsnu / k;
sqsne = sqsne / k;

snksq = snk * snk;
snusq = snu * snu;
snesq = sne * sne;
	fprintf(op,"%.4f\t",(double)snk);
	fprintf(op,"%.4f\t",(double)snu);
	fprintf(op,"%.4f\n",(double)sne);
sk = sqrt(fabs(fabs(snksq) - fabs(sqsnk)));
su = sqrt(fabs(fabs(snusq) - fabs(sqsnu)));
se = sqrt(fabs(fabs(snesq) - fabs(sqsne)));

	//fprintf(op,"%.4f\t",(double)sqsnk / (k * k));
	//fprintf(op,"%.4f\t",(double)sqsnu / (k * k));
	//fprintf(op,"%.4f\n",(double)sqsne / (k * k));

	//fprintf(op,"%.4f\t",(double)snksq / (k * k));
	//fprintf(op,"%.4f\t",(double)snusq / (k * k));
	//fprintf(op,"%.4f\n",(double)snesq / (k * k));
fprintf(op,"%.4f\t", sk);
fprintf(op,"%.4f\t", su);
fprintf(op,"%.4f\n", se);

survk = (double)deathk / k;
surve = (double)deathe / k;
survu = (double)deathu / k;	
statk = gamma * sk / sqrt(k);
statu = gamma * su / sqrt(k);
state = gamma * se / sqrt(k);
fprintf(op,"%.4f\t", statk);
fprintf(op,"%.4f\t", statu);
fprintf(op,"%.4f\n", state);

fprintf(op,"%.4f\t", survk);
fprintf(op,"%.4f\t", survu);
fprintf(op,"%.4f\n", surve);

theorsurvk = 1 * pk1 + 2 * pk2 + 3 * pk3 + 4 * pk4;
theorsurvu = 1 * pu1 + 2 * pu2 + 3 * pu3 + 4 * pu4;
theorsurve = 1 * pe1 + 2 * pe2 + 3 * pe3 + 4 * pe4;

fprintf(op,"%.4f\t", theorsurvk);
fprintf(op,"%.4f\t", theorsurvu);
fprintf(op,"%.4f\n", theorsurve);

//fprintf(op,"%ld\t", snksq);
//fprintf(op,"%ld\n", sqsnk);
	close(op);
	return 0;
}
