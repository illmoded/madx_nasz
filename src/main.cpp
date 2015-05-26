#include "magnesy.h"
#include "generate.h"

int main(int argc, char const *argv[])
{
	unsigned int rdzenie;
	rdzenie=std::thread::hardware_concurrency();
	remove("output.txt");
	gen(10000);

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
	// for (int i = 0; i < magnes_vec.size(); i++){
	// 	cout << i+1 << "\t" << magnes_vec[i]->GetPolozenie() << "\t" << magnes_vec[i]->GetDlugosc() << "\t" << magnes_vec[i]->GetIndukcja() << "\t" << magnes_vec[i]->Kto() << endl;
	// }

	ifstream plik("input.txt",ios::in);
	std::vector<proton> proton_vec;
	proton_vec=wczytajprotony(plik);
	plik.close();

	// cout << proton_vec.size() << endl;
	// for (int i = 0; i < proton_vec.size(); i++){
	// 	cout << i+1 << "\t" << proton_vec[i].energia << endl;
	// }

	std::vector<proton> proton_tab[rdzenie];
	int I=proton_vec.size()/rdzenie;
	for(int i = 0; i < rdzenie; i++){
		std::vector<proton>::const_iterator first = proton_vec.begin()+i*I;
		std::vector<proton>::const_iterator last = proton_vec.begin()+(i+1)*I;
		std::vector<proton> proton_temp(first, last);
		proton_tab[i] = proton_temp;
		proton_temp.clear();
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