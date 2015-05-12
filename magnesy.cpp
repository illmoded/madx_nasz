//czas P+K ~1h P20m+10m K2h+niewiemile

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <memory> // do unique_ptr
// #include <typeinfo> //do nazw klas

using namespace std;

class magnes
{
public:
	double polozenie;
	double dlugosc;
	double indukcja; // wsp k
	int name;

	virtual double pole() //trzeba inicjalizować funkcje wirtualne
	{
		return 0;
	}
	virtual void kto()
	{
		name=0;
	}
	// string s = typeid(magnes).name(); //odtąd s jest nazwą klasy
};

class dipol:public magnes
{
public:
	virtual double pole();
	virtual void kto();
};

class kwadrupol:public magnes
{
public:
	virtual double pole(double x, double y);
	virtual void kto();
};

	double dipol::pole()
	{
		return indukcja;
	}

	void dipol::kto()
	{
		name=2;
	}

	double kwadrupol::pole(double x, double y)
	{	
		return indukcja*(x*x+y*y);
	}

	void kwadrupol::kto()
	{
		name=4;
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

std::vector<std::unique_ptr<magnes>> wczytajmagnesy(std::ifstream &plik)
{
	//może do jakiejś klasy?
	std::vector<std::unique_ptr<magnes>> lista;	
	double a,b,c,d;
	dipol *dip = new dipol();
	kwadrupol *kwa = new kwadrupol();

	int i=0;
	int j=1;

	while(plik >> a >> b >> c >> d)
	{
		if (d==2)
		{
			lista.push_back(std::unique_ptr<magnes>(dip));
		}
		else if (d==4)
		{
			lista.push_back(std::unique_ptr<magnes>(kwa));
		}
		else
		{
			cout << "Błąd w " << j << " magnesie. Czy to dipol czy kwadrupol? Oto jest pytanie." << endl << "Hehe" << endl;
			j++;
			continue;
		}
		lista[i]->polozenie=a;
		lista[i]->dlugosc=b;
		lista[i]->indukcja=c;
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
	std::vector<std::unique_ptr<magnes>> listamagnesow;

	if(argc==1){
		ifstream plik("def_magn",ios::in);
		listamagnesow=wczytajmagnesy(plik);
		plik.close();
	}
	// else
	// 	for (int i = 0; i < argc; i++)
	// 	{
	// 		ifstream plik(argv[i],ios::in);
	// 		listamagnesow=vappend(listamagnesow,wczytajmagnesy(plik));
	// 		plik.close();
	// 	}

	// cout << listamagnesow.size() << endl;
	for (int i = 0; i < listamagnesow.size(); i++)
	{
		listamagnesow[i]->kto();
		cout << i+1 << "\t" << listamagnesow[i]->name << endl;
	}

	ifstream plik("input",ios::in);

	std::vector<proton> protony;
	protony=wczytajprotony(plik);
	plik.close();

	// cout << protony.size() << endl;

	ofstream zapis("output",ios::out);

	double energiaa=1/protony[0].energia; //jest taka sama dla wszystkich, program też zwalnia, ale nie aż tak bardzo

/*	for (int i = 0; i < protony.size(); i++)
	{	
		

		double dt=0.001;
		while(protony[i].z<l && protony[i].x*protony[i].x+protony[i].y*protony[i].y<r*r)
		{
			protony[i].x+=dt*protony[i].px*energiaa; //wprowadzenie tutaj dzielenia przez energie spowalnia program niesamowicie
			protony[i].y+=dt*protony[i].py*energiaa; //mnożenie jest szybsze?
			protony[i].z+=dt*protony[i].pz*energiaa;

			for (int j = 0; j < listamagnesow.size(); j++)
			{
				while(protony[i].z>listamagnesow[j].polozenie && protony[i].z<listamagnesow[j].polozenie+listamagnesow[j].dlugosc)
				{	
					//funkcje na pole - jakoś, tak z indukcją to w ogóle działa?
					double E=protony[i].energia;	//może wywalić, jest taka sama dla wszystkich 			
					double Bx=listamagnesow[j].indukcja;
					double By=listamagnesow[j].indukcja;
					protony[i].px+=dt/E/E*protony[i].pz*By; //mnożenie!?!?!?
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

	zapis.close();*/
	return 0;
}