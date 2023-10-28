#pragma once
#include "produs.h"
#include <vector>
using std::vector;
class Repo_virtual {
public:
	//stocheaza un produs
	virtual void store(const Produs& p)=0;
	//sterge produsul cu numele nume
	virtual void sterge(string nume)=0;
	//modifica un produs dupa nume
	virtual void modifica(string nume, const Produs& new_p)=0;
	//returneaza numarul de produse
	virtual size_t size()const=0;
	//returneaza un vector cu produsele
	virtual const vector<Produs> get_all()=0;
	//cauta produsul in lista
	virtual std::vector<Produs>::iterator cauta(string nume)=0;
	virtual ~Repo_virtual() = default;

};