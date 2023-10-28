#pragma once
#include "produs.h"
#include <vector>
using std::vector;
class Cos {
private:
	vector<Produs> cos;
public:
	//goleste cosul de cumparaturi
	void goleste_cos();
	//adaugaa un produs in lista de cumparaturi
	void adauga_produs_in_cos(const Produs& p);
	//adauga un cos in lista de cumparaturi
	void adauga_random_cos(vector<Produs> produse, int howMany);
	//returneaza toate produsele din cos
	vector<Produs> get_all_cos();


};

void teste_cos();