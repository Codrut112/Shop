#include "cos.h"
#include "repo.h"
#include <algorithm>
#include <random>
#include <assert.h>
using std::shuffle;
void Cos::goleste_cos()
{
	cos.clear();

}

void Cos::adauga_produs_in_cos(const Produs& p)
{
	
	cos.push_back(p);
}

void Cos::adauga_random_cos(vector<Produs> produse, int howMany)
{   
	
    if (produse.size() == 0)throw RepoException("nu exista produse de adaugat in cos");
	shuffle(produse.begin(), produse.end(), std::default_random_engine(std::random_device{}()));
	vector<Produs> copie_produse=produse;

	while (cos.size() < howMany) {
		if (copie_produse.size() == 0)
		{
			shuffle(produse.begin(), produse.end(), std::default_random_engine(std::random_device{}()));
		 copie_produse = produse;

		}
		cos.push_back(copie_produse.back());
		copie_produse.pop_back();


	}
	copie_produse.clear();
}

vector<Produs> Cos::get_all_cos()
{
	return cos;
}


void teste_cos()
{
	Cos cos;
	vector<Produs> carucior;
	Produs p1{ 22,"nume","producator","tip" };
	Produs p2{ 22.5,"numele","producatorul","tipul" };
	carucior.push_back(p1);
	carucior.push_back(p2);
	cos.adauga_produs_in_cos(p1);
	cos.adauga_produs_in_cos(p2);
	assert(cos.get_all_cos().size() == 2);
	cos.adauga_random_cos(carucior, 5);
	assert(cos.get_all_cos().size() == 5);
	cos.goleste_cos();
	assert(cos.get_all_cos().size() == 0);
}
