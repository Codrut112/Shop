#pragma once
#include <vector>
#include "produs.h"
#include "vector.h"
#include "repo_virtual.h"
using std::vector;
class Repo:public Repo_virtual {
private:
	vector<Produs> produse;
public:
	//constructor default
	Repo() = default;
	//impiedica crearea de copii
	Repo(const Repo& ot) = delete;
	//stocheaza un produs
	virtual void store(const Produs& p);
	//sterge produsul cu numele nume
	virtual void sterge(string nume);
	//modifica un produs dupa nume
	virtual void modifica(string nume,const Produs& new_p);
	//returneaza numarul de produse
	virtual size_t size()const;
	//returneaza un vector cu produsele
	virtual const vector<Produs> get_all()  ;
	//cauta produsul in lista
	virtual std::vector<Produs>::iterator cauta(string nume);
};

class RepoException {
private:
	string msg;
public:
	RepoException(string m);
	//returneaza eroarea
	string get_message();
	
	
};


void test_repo();