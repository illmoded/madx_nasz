#ifndef MAGNESY_
#define MAGNESY_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;

class magnes
{
private:
	double polozenie;
	double dlugosc;
	double indukcja;

public:
	virtual std::vector<double> pole(double x, double y);
    virtual std::string Kto();
	void SetPolozenie(double P);
	double GetPolozenie();
	void SetDlugosc(double P);
	double GetDlugosc();
	void SetIndukcja(double P);
	double GetIndukcja();
};

class dipol:public magnes
{
public:
	virtual std::vector<double> pole(double x, double y);
    virtual std::string Kto();
};

class kwadrupolX:public magnes
{
public:
	virtual std::vector<double> pole(double x, double y);
    virtual std::string Kto();
};

class kwadrupolY:public magnes
{
public:
    virtual std::vector<double> pole(double x, double y);
    virtual std::string Kto();
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

std::vector<proton> wczytajprotony(std::ifstream &plik);
std::vector<magnes_ptr> wczytajmagnesy(std::ifstream &plik);
std::vector<magnes_ptr> wczytajjeden(double l, double d, double i, std::string m);
std::vector<magnes_ptr> vappend(std::vector<magnes_ptr> a, std::vector<magnes_ptr> b);


void lock(std::string const& msg);
void oblicz(std::vector<magnes_ptr> magnesy, std::vector<proton> protony, double l, double r);
void wypiszmagnesy(std::vector<magnes_ptr> magnes);

#endif
