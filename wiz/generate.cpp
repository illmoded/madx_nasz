#include "generate.h"

using namespace std;
const double E0=7000;
const double pmax=3.;
const double ksimax=0.5;
const double fimax=2*M_PI;
const double M=0.9383;
double pmin=0., ksimin=0., fimin=0.;
double p, ksi, fi, r, E;

void gen(int ilosc)
{	
	fstream plik;
	plik.open("input.txt",fstream::out);
	srand ((unsigned)time(NULL));

	for(int i=1; i<ilosc; i++)
	{
		r=(double)rand()/RAND_MAX;
		p = pmin + (pmax-pmin)*r;

		r=(double)rand()/RAND_MAX;
		ksi = ksimin + (ksimax-ksimin)*r;

		r=(double)rand()/RAND_MAX;
		fi = fimin + (fimax-fimin)*r;

		E=E0*(1-ksi);
		plik << 0 << "\t" << 0 << "\t" << 0 << "\t" << p*cos(fi) << "\t" << p*sin(fi)+142.5e-6 << "\t" << sqrt(E*E-M*M) << "\t" << E << endl;
	}

    plik.close();
}
