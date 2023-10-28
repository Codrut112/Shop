#include "repo.h"
#include <assert.h>
#include <iostream>
#include <algorithm>

void Repo::store(const Produs& p)
{
	

	 auto rez=std::find_if(produse.begin(), produse.end(), [&p](const Produs& produs) {return  (p.get_nume() == produs.get_nume() and p.get_producator() == produs.get_producator() and p.get_tip() == produs.get_tip());
		 });

	if (rez != produse.end())
		throw RepoException("produs existent");

	
	produse.push_back(p);

}

void Repo::sterge(string nume)
{
	auto produs = produse[produse.size() - 1];
	std::vector<Produs>::iterator poz = cauta(nume);
	*poz = produs;
	produse.pop_back();
}

void Repo::modifica(string nume, const Produs& new_p)
{
	std::vector<Produs>::iterator poz = cauta(nume);
	*poz=new_p;
}

size_t Repo::size()const
{
	return produse.size();

}

const vector<Produs> Repo::get_all() 
{
	return produse;
}

std::vector<Produs>::iterator Repo::cauta(string nume )
{

	auto rez = std::find_if(produse.begin(), produse.end(), [ nume](const Produs& p) {return p.get_nume() == nume; });

	if(rez==produse.end())throw RepoException("produs inexistent");
	return rez;
}


void test_repo()
{
	
	Repo lista;
	lista.store(Produs(1, "Apa", "dorna", "minerala"));
	lista.store(Produs(2.5, "Apa", "dorna", "plata"));
	try {
		lista.store(Produs(2.5, "Apa", "dorna", "plata"));
		assert(false);
	}
	catch (RepoException e) { assert(true); }
	
	
	assert(lista.size() == 2);

	lista.modifica("Apa", Produs(1, "bere", "cicucas", "rece"));
	vector<Produs> lista_noua = lista.get_all();
	assert(lista_noua.front().get_nume() == "bere");

	
	try {
		lista.cauta("");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "produs inexistent");
		assert(true);
	}

	lista.sterge("Apa");
	assert(lista.size() == 1);
	

}


RepoException::RepoException(string m)
{
	msg = m;
}

string RepoException::get_message()
{
	return msg;
}
