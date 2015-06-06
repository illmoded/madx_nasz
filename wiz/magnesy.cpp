#include "magnesy.h"

using namespace std;

    std::vector<double> magnes::pole(double x, double y)
	{
		std::vector<double> vec;
		return vec;
	}

    std::string magnes::Kto()
	{
        return "M";
	}

	void magnes::SetPolozenie(double P)
	{
		polozenie = P;
	}

	double magnes::GetPolozenie()
	{
		return polozenie;
	}

	void magnes::SetDlugosc(double P)
	{
		dlugosc = P;
	}

	double magnes::GetDlugosc()
	{
		return dlugosc;
	}

	void magnes::SetIndukcja(double P)
	{
		indukcja = P;
	}

	double magnes::GetIndukcja()
	{
		return indukcja;
	}

	std::vector<double> dipol::pole(double x, double y)
	{
		std::vector<double> vec;
		vec.clear();
		double I = GetIndukcja();
		vec.push_back(I);
		vec.push_back(0);
		return vec;
	}

    std::string dipol::Kto()
	{
        return "D";
	}

    std::vector<double> kwadrupolX::pole(double x, double y)
	{
		std::vector<double> vec;
		vec.clear();
		double I = GetIndukcja();
        vec.push_back(I*y);
		vec.push_back(I*x);
		return vec;
	}

    std::string kwadrupolX::Kto()
	{
        return "KX";
	}

    std::vector<double> kwadrupolY::pole(double x, double y)
    {
        std::vector<double> vec;
        vec.clear();
        double I = GetIndukcja();
        vec.push_back(I*y);
        vec.push_back(I*x);
        return vec;
    }

    std::string kwadrupolY::Kto()
    {
        return "KY";
    }

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
    double a, b, c;
    std::string d;

    int i=0;
    int j=1;

    while(plik >> a >> b >> c >> d)
    {
        if (d=="D")
        {
            magnes_ptr D(new dipol);
            lista.push_back(D);
        }
        else if (d=="KX")
        {
            magnes_ptr KX(new kwadrupolX);
            lista.push_back(KX);
        }
        else if (d=="KY")
        {
            magnes_ptr KY(new kwadrupolY);
            lista.push_back(KY);
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

std::vector<magnes_ptr> wczytajjeden(double l, double d, double i, std::string m)
{
    std::vector<magnes_ptr> lista;
    if (m=="D")
    {
        magnes_ptr D(new dipol);
        lista.push_back(D);
        lista[0]->SetPolozenie(l);
        lista[0]->SetDlugosc(d);
        lista[0]->SetIndukcja(i);
    }
    else if (m=="KX")
    {
        magnes_ptr KX(new kwadrupolX);
        lista.push_back(KX);
        lista[0]->SetPolozenie(l);
        lista[0]->SetDlugosc(d);
        lista[0]->SetIndukcja(i);
    }
    else if (m=="KY")
    {
        magnes_ptr KY(new kwadrupolY);
        lista.push_back(KY);
        lista[0]->SetPolozenie(l);
        lista[0]->SetDlugosc(d);
        lista[0]->SetIndukcja(i);
    }
    else cout << "Błąd" << endl;

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
                    dt=0.05;
					double Bx=magnesy[j]->pole(protony[i].x, protony[i].y)[0];
					double By=magnesy[j]->pole(protony[i].x, protony[i].y)[1];
                    protony[i].px+=dt/E*protony[i].pz*By;
                    protony[i].py+=dt/E*protony[i].pz*Bx;
                    protony[i].pz+=dt/E*(protony[i].px*By-protony[i].py*Bx);
					protony[i].x+=dt/E*protony[i].px;
					protony[i].y+=dt/E*protony[i].py;
					protony[i].z+=dt/E*protony[i].pz;
					E = sqrt(protony[i].px*protony[i].px+protony[i].py*protony[i].py+protony[i].pz*protony[i].pz+Mp*Mp);
				}
                dt=0.1;
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

void wypiszmagnesy(std::vector<magnes_ptr> magnes)
{
    cout << "Liczba wczytanych magnesów: " << magnes.size() << endl;
    for (int i = 0; i < magnes.size(); i++){
        cout << i+1 << "\t" << magnes[i]->GetPolozenie() << "\t" << magnes[i]->GetDlugosc() << "\t" << magnes[i]->GetIndukcja() << "\t" << magnes[i]->Kto() << endl;
    }
}
