#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <thread>
#include <mutex>

using namespace std;

class magnes
{
public:
	double polozenie;
	double dlugosc;
	double indukcja;
	int name;

	virtual double pole(double, double)
	{
		return 0;
	}
	virtual void kto()
	{
		name=0;
	}
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

typedef boost::shared_ptr<magnes> magnes_ptr;

std::vector<proton> wczytajprotony(std::ifstream &plik)
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

std::vector<magnes_ptr> wczytajmagnesy(std::ifstream &plik)
{
	std::vector<magnes_ptr> lista;	
	double a,b,c,d;
	magnes_ptr D(new dipol);
	magnes_ptr K(new kwadrupol);

	int i=0;
	int j=1;

	while(plik >> a >> b >> c >> d)
	{
		if (d==2)
		{
			lista.push_back(D);
		}
		else if (d==4)
		{
			lista.push_back(K);
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
		i++;
		j++;
	}
	return lista;	
}

std::vector<magnes_ptr> vappend(std::vector<magnes_ptr> a, std::vector<magnes_ptr> b)
{
	a.reserve(a.size() + b.size());
	a.insert(a.end(), std::make_move_iterator(b.begin()), std::make_move_iterator(b.end()));
	b.clear();
	return a;
}

std::mutex blokada;

void lock(std::string const& msg)
{
	blokada.lock();
    ofstream zapis("output.txt",ios::app);

    zapis << msg << endl;

	zapis.close();  
    blokada.unlock();
}

void oblicz(std::vector<magnes_ptr> magnesy, std::vector<proton> protony, double l, double r)
{
	double dt=0.001;
	for (int i = 0; i < protony.size(); i++)
	{	
		while(protony[i].z<l && protony[i].x*protony[i].x+protony[i].y*protony[i].y<r*r)
		{
			double energiaa=1./protony[i].energia;
			protony[i].x+=dt*protony[i].px*energiaa;
			protony[i].y+=dt*protony[i].py*energiaa;
			protony[i].z+=dt*protony[i].pz*energiaa;

			for (int j = 0; j < magnesy.size(); j++)
			{
				while(protony[i].z>magnesy[j]->polozenie && protony[i].z<magnesy[j]->polozenie+magnesy[j]->dlugosc)
				{	
					double E=protony[i].energia;		
					double Bx=magnesy[j]->pole(protony[i].x, protony[i].y);
					double By=magnesy[j]->pole(protony[i].x, protony[i].y);
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
		{
			std::string zapis;
			std::stringstream ss(zapis);
			ss << i+1 << "\t" << protony[i].x << "\t" << protony[i].px << "\t" << protony[i].y << "\t" << protony[i].py
		 	<< "\t" << protony[i].pz << "\t" << protony[i].energia;
		 	// cout << ss.str() << endl;
		 	zapis = ss.str();
		 	lock(zapis);
		}
	}
}

int main(int argc, char const *argv[])
{
	unsigned int rdzenie;
	rdzenie=std::thread::hardware_concurrency();
	remove("output.txt");

	if (rdzenie==0) //czyli że nie wykrywa
	{
		rdzenie=2;
	}

	double l=204.0;
	double r=0.002;
	std::vector<magnes_ptr> magnes_vec;
	std::vector<magnes_ptr> magnes_temp;

	if(argc==1){
		ifstream plik("def_magn.mag",ios::in);
		magnes_vec = wczytajmagnesy(plik);
		plik.close();
	}
	else 
		for (int i = 1; i <= argc; i++){
			ifstream plik(argv[i],ios::in);
			magnes_temp = wczytajmagnesy(plik);
			magnes_vec = vappend(magnes_vec, magnes_temp);
			plik.close();
		}

	// cout << magnes_vec.size() << endl;
	// for (int i = 0; i < magnes_vec.size(); i++)
	// {
	// 	magnes_vec[i]->kto();
	// 	cout << i+1 << "\t" << magnes_vec[i]->name << endl;
	// }

	ifstream plik("input.txt",ios::in);
	std::vector<proton> proton_vec;
	proton_vec=wczytajprotony(plik);
	plik.close();

	// cout << proton_vec.size() << endl;

	std::vector<proton> proton_tab[rdzenie];
	int I=proton_vec.size()/rdzenie;
	for(int i = 0; i < rdzenie; i++){
		std::vector<proton>::const_iterator first = proton_vec.begin()+i*I;
		std::vector<proton>::const_iterator last = proton_vec.begin()+(i+1)*I;
		std::vector<proton> proton_temp(first, last);
		proton_tab[i] = proton_temp;
	}

	std::thread thr[rdzenie];
	for (int i = 0; i < rdzenie; i++)
	{
		thr[i]=std::thread(oblicz, magnes_vec, proton_tab[i], l, r);
	}

	for (int i = 0; i < rdzenie; i++)
	{
		thr[i].join();
	}

	return 0;
}