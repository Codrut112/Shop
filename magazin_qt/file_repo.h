#pragma once
#include "repo_virtual.h"
#include "repo.h"
class RepoFile :public Repo_virtual {
private:
	std::string fName;
	vector<Produs> produse;
	void loadFromFile();
	void writeToFile();
	
public:
	RepoFile(std::string fName):fName{ fName } {
		loadFromFile();
	};
	void store(const Produs& p) override {
		
		auto rez = std::find_if(produse.begin(), produse.end(), [&p](const Produs& produs) {return  (p.get_nume() == produs.get_nume() and p.get_producator() == produs.get_producator() and p.get_tip() == produs.get_tip());
			});

		if (rez != produse.end())
			throw RepoException("produs existent");


		produse.push_back(p);

		writeToFile();
	}
	void sterge(string nume) override {
	
		auto produs = produse[produse.size() - 1];
		std::vector<Produs>::iterator poz = cauta(nume);
		*poz = produs;
		produse.pop_back();
		writeToFile();
	}
	void modifica(string nume, const Produs& new_p) {
		std::vector<Produs>::iterator poz = cauta(nume);
		*poz = new_p;
		writeToFile();
   }
	size_t size()const {
		return produse.size();

}
	virtual const vector<Produs> get_all() {
		return produse;
	}
	virtual std::vector<Produs>::iterator cauta(string nume) {
	
		auto rez = std::find_if(produse.begin(), produse.end(), [nume](const Produs& p) {return p.get_nume() == nume; });

		if (rez == produse.end())throw RepoException("produs inexistent");
		return rez;
}
};

void test_file_repo();