#include "magnesy.h"

using namespace std;

class magnes
{
private:
	double polozenie;
	double dlugosc;
	double indukcja;

public:
	virtual std::vector<double> pole(double x, double y)
	{
		std::vector<double> vec;
		return vec;
	}

	virtual char Kto()
	{
		return 'M';
	}

	void SetPolozenie(double P)
	{
		polozenie = P;
	}

	double GetPolozenie()
	{
		return polozenie;
	}

	void SetDlugosc(double P)
	{
		dlugosc = P;
	}

	double GetDlugosc()
	{
		return dlugosc;
	}

	void SetIndukcja(double P)
	{
		indukcja = P;
	}

	double GetIndukcja()
	{
		return indukcja;
	}
};

class dipol:public magnes
{
public:
	virtual std::vector<double> pole(double x, double y)
	{
		std::vector<double> vec;
		vec.clear();
		double I = GetIndukcja();
		vec.push_back(I);
		vec.push_back(0);
		return vec;
	}

	virtual char Kto()
	{
		return 'D';
	}
};

class kwadrupol:public magnes
{
public:
	virtual std::vector<double> pole(double x, double y)
	{
		std::vector<double> vec;
		vec.clear();
		double I = GetIndukcja();
		vec.push_back(I*y);
		vec.push_back(I*x);
		return vec;
	}

	virtual char Kto()
	{
		return 'K';
	}
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

typedef std::shared_ptr<magnes> magnes_ptr;

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
	double a, b, c, d;

	int i=0;
	int j=1;

	while(plik >> a >> b >> c >> d)
	{	
		if (d==2)
		{
			magnes_ptr D(new dipol);
			lista.push_back(D);
		}
		else if (d==4)
		{
			magnes_ptr K(new kwadrupol);
			lista.push_back(K);
		}
		else
		{
			cout << "Błąd w " << j << " magnesie. Czy to dipol czy kwadrupol? Oto jest pytanie." << endl << "Hehe" << endl;
			j++;
			continue;
		}
		lista[i]->SetPolozenie(a);
		lista[i]->SetDlugosc(b);
		lista[i]->SetIndukcja(c);
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
	double Mp = 0.9383;
	double dt=0.1;
	for (int i = 0; i < protony.size(); i++)
	{	
		double E = protony[i].energia;
		while(protony[i].z<l && protony[i].x*protony[i].x+protony[i].y*protony[i].y<r*r)
		{
			protony[i].x+=dt*protony[i].px/E;
			protony[i].y+=dt*protony[i].py/E;
			protony[i].z+=dt*protony[i].pz/E;

			for (int j = 0; j < magnesy.size(); j++)
			{
				while(protony[i].z>magnesy[j]->GetPolozenie() && protony[i].z<magnesy[j]->GetPolozenie()+magnesy[j]->GetDlugosc())
				{	
					double Bx=magnesy[j]->pole(protony[i].x, protony[i].y)[0];
					double By=magnesy[j]->pole(protony[i].x, protony[i].y)[1];
					protony[i].px+=dt/E/E*protony[i].pz*By;
					protony[i].py+=dt/E/E*protony[i].pz*Bx;
					protony[i].pz+=dt/E/E*(protony[i].px*By-protony[i].py*Bx);
					protony[i].x+=dt/E*protony[i].px;
					protony[i].y+=dt/E*protony[i].py;
					protony[i].z+=dt/E*protony[i].pz;
					E = sqrt(protony[i].px*protony[i].px+protony[i].py*protony[i].py+protony[i].pz*protony[i].pz+Mp*Mp);
				}
			}
		}

		// cout << "[" << 1000*i/protony.size()/10. << '%' << "]   " << "\r";
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
