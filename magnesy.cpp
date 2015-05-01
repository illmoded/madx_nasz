//czas P+K ~1h P20m+10m K25min

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
	double indukcja; /// wsp k
};

class dipol:public magnes
{
public:
	void poledipola(double x);	
};

class kwadrupol:public magnes
{
public:
	void polekwadrupola(double x, double y);	
};

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
	double a,b,c,d,e,f,g;
	proton prot;

	int i=0;

	while(plik >> a >> b >> c >> d >> e >> f >> g)
	{
		listap.push_back(prot);
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
	double L=204.0;
	std::vector<magnes> listamagnesow;	

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
	// cout << listamagnesow.size() << endl;	

	// for (int i = 0; i < listamagnesow.size(); i++)
	// {
	// 	cout << listamagnesow[i].polozenie << endl;
	// }

	ifstream plik("czastki",ios::in); //trzeba je jeszcze gdzieś tworzyć



	std::vector<proton> protony;
	protony=wczytajprotony(plik);
	plik.close();

	// cout << protony.size() << endl;



	///ruch, później może do innej funkcji
	///eulerem, po co sie meczyc z czyms innym
	for (int i = 0; i < protony.size(); i++)
	{
		double t;
		double dt=0.01;
		while(protony[i].z<L) //gdzie są osie? no i trzeba by dodać jakoś zapisywanie trajektorii, chyba że sam bufor openGL wystarczy
		{
			// x+=px*t;
			// y+=py*t;
			// z+=pz*t;
			t+=dt;
			for (int j = 0; j < listamagnesow.size(); j++)
			{
				while(protony[i].z>listamagnesow[j].polozenie && protony[i].z<listamagnesow[j].polozenie+listamagnesow[j].dlugosc)
				{
					//x+=pole dipola /kwadrupola tylko że są voidami i nie wiem jak wyglądają i czy to nie ma być jakoś relatywistycznie
					//y+=tak samo
				}
			}
		}		
	}

	return 0;
}
