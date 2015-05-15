#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;
const double E0=7000;
const double pmax=3.;
const double ksimax=.2;
const double fimax=2*M_PI;
int I=1000;			//liczba czastek
const double M=0.9383;
double pmin=0., ksimin=0., fimin=0.;;
double p, ksi, fi, r, E;

int main(int argc, char const *argv[])
{	
	fstream plik;
	plik.open("input.txt",fstream::out);
	int id=1;
	if(argc>1) I = atoi(argv[1])+1;
	srand ((unsigned)time(NULL));

	for(int i=1; i<I; i++)
	{
		r=(double)rand()/RAND_MAX;
		p = pmin + (pmax-pmin)*r;

		r=(double)rand()/RAND_MAX;
		ksi = ksimin + (ksimax-ksimin)*r;

		r=(double)rand()/RAND_MAX;
		fi = fimin + (fimax-fimin)*r;

		E=E0*(1-ksi);
		plik << 0 << "\t" << 0 << "\t" << 0 << "\t" << p*cos(fi) << "\t" << p*sin(fi) << "\t" << sqrt(E*E-M*M) << "\t" << E << endl;
	}

    plik.close();

	return 0;
}