//czas P+K ~1h P20m+10m K2h+niewiemile

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

class magnes
{
public:
	double polozenie;
	double dlugosc;
	double indukcja; // wsp k
};

class dipol:public magnes
{
public:
	double pole();
	void kto();
};

class kwadrupol:public magnes
{
public:
	double pole(double x, double y);
	void kto();
};

	double dipol::pole()
	{
		return dipol::indukcja;
	}

	void dipol::kto()
	{
		cout << "dipol" << endl;
	}

	double kwadrupol::pole(double x, double y)
	{
		return kwadrupol::indukcja*(x*x+y*y);
	}

	void kwadrupol::kto()
	{
		cout << "kwadrupol" << endl;
	}

class proton
{
public:
	double x;
	double y;
	double z;
	double px;
	double py;
	double pz;
	double energia;
};

std::vector<proton>wczytajprotony(std::ifstream &plik)
{
	std::vector<proton> listap;
	double a, b, c, d, e, f, g;
	proton proton_;

	int i=0;

	while(plik >> a >> b >> c >> d >> e >> f >> g)
	{
		listap.push_back(proton_);
		listap[i].x=a;
		listap[i].y=b;
		listap[i].z=c;
		listap[i].px=d;
		listap[i].py=e;
		listap[i].pz=f;
		listap[i].energia=g;

		i++;
	}
	return listap;
}

std::vector<magnes>wczytajmagnesy(std::ifstream &plik)
{
	//może do jakiejś klasy?
	std::vector<magnes> lista;	
	double a,b,c,d;
	dipol dip;
	kwadrupol kwa;

	int i=0;
	int j=1;

	while(plik >> a >> b >> c >> d)
	{
		if (d==2)
		{
			lista.push_back(dip);
		}
		else if (d==4)
		{
			lista.push_back(kwa);
		}
		else
		{
			cout << "Błąd w " << j << " magnesie. Czy to dipol czy kwadrupol? Oto jest pytanie." << endl << "Hehe" << endl;
			j++;
			continue;
		}
		lista[i].polozenie=a;
		lista[i].dlugosc=b;
		lista[i].indukcja=c;
		i++;j++;
	}
	return lista;	
}

//fstream a("temp.txt", ios::in); konstruktor domyślny, bez .open(), zamiast nazwy argv?

std::vector<magnes>vappend(std::vector<magnes> a, std::vector<magnes> b)
{
	//moze powinien byc void?
	a.reserve(a.size() + b.size());
	a.insert(a.end(), b.begin(), b.end());
	b.clear();
	return a;
}


int main(int argc, char const *argv[])
{
	double l=204.0;
	double r=0.002;
	std::vector<magnes> listamagnesow;	//a jak sie teraz odwolac do samych dipoli lub kwadrupoli w liscie?

	if(argc==1){
		ifstream plik("def_magn",ios::in);
		listamagnesow=vappend(listamagnesow,wczytajmagnesy(plik));
		plik.close();
	}
	else
		for (int i = 0; i < argc; i++)
		{
			ifstream plik(argv[i],ios::in);
			listamagnesow=vappend(listamagnesow,wczytajmagnesy(plik));
			plik.close();

		}

	dipol D;
	kwadrupol K;
	// cout << listamagnesow.size() << endl;

	// for (int i = 0; i < listamagnesow.size(); i++)
	// {
	// 	cout << i+1 << "\t" << listamagnesow[i].polozenie << endl;
	// }

	ifstream plik("input",ios::in);

	std::vector<proton> protony;
	protony=wczytajprotony(plik);
	plik.close();

	// cout << protony.size() << endl;

	ofstream zapis("output",ios::out);

	for (int i = 0; i < protony.size(); i++)
	{
		double dt=0.001;
		while(protony[i].z<l && protony[i].x*protony[i].x+protony[i].y*protony[i].y<r*r)
		{
			protony[i].x+=dt*protony[i].px; //wprowadzenie tutaj dzielenia przez energie spowalnia program niesamowicie
			protony[i].y+=dt*protony[i].py;
			protony[i].z+=dt*protony[i].pz;

			for (int j = 0; j < listamagnesow.size(); j++)
			{
				while(protony[i].z>listamagnesow[j].polozenie && protony[i].z<listamagnesow[j].polozenie+listamagnesow[j].dlugosc)
				{	
					double E=protony[i].energia;				
					double Bx=listamagnesow[j].indukcja;
					double By=listamagnesow[j].indukcja;
					protony[i].px+=dt/E/E*protony[i].pz*By;
					protony[i].py+=dt/E/E*protony[i].pz*Bx;
					protony[i].pz+=dt/E/E*(protony[i].px*By-protony[i].py*Bx);
					protony[i].x+=dt/E*protony[i].px;
					protony[i].y+=dt/E*protony[i].py;
					protony[i].z+=dt/E*protony[i].pz;
				}
			}
		}

		cout << "[" << 1000*i/protony.size()/10. << '%' << "]   " << "\r";
		if(protony[i].x*protony[i].x+protony[i].y*protony[i].y<r*r)
			zapis << i+1 << "\t" << protony[i].x << "\t" << protony[i].px << "\t" << protony[i].y << "\t" << protony[i].py
		 	<< "\t" << protony[i].pz << "\t" << protony[i].energia << endl;
	}

	zapis.close();
	return 0;
}