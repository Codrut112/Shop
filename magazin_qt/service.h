#pragma once
#include "file_repo.h"
#include "validare.h"
#include "cos.h"
#include <map>
#include <fstream>
#include "repo_virtual.h"
#include "undo.h"
#include "observer.h"
using std::unique_ptr;
using std::string;
using std::map;
class Magazin:public Subject {
	Repo_virtual& rep;
	Validator& validator;
    Cos cos;
	vector<unique_ptr<ActiuneUndo>>undoActions;	
public:
	//constructor
	Magazin(Repo_virtual& rep, Validator validator, Cos cos) :rep{ rep }, validator{ validator }, cos{ cos } {};
	//impiedica copierea
	Magazin(const Magazin& ot) = delete;
	
	//adauga un produs 
	void adauga(double pret, string nume, string producator, string tip);
	//modifica un produs dupa nume
	void modifica(double pret_nou, string nume, string producator_nou, string tip_nou);
	//sterge un produs dupa nume
	void sterge(string nume);
	//returneaza un vector cu toate elementele
	const vector<Produs> get_all()const;
	//returneaza numarul de produse
	size_t size()const;
	//returneaza un vector cu toate produsele cu pretul mai mare
	const vector<Produs> filtrare_pret(double pret_minim)const;
	//returneaza un vector cu toate produsele cu numele "nume"
	const vector<Produs> filtrare_nume(string nume)const;
	//returneaza un vector cu toate produsele de la un anumit producator
	const vector<Produs> filtrare_producator(string producator)const;

	void adauga_produs_cos(string nume);
	void adauga_produse_random(int howMany);
	void goleste_cos();
	const vector<Produs> get_all_cos();
	typedef bool(*compara)(Produs x, Produs y);
	vector<Produs> sortare(compara cmp);
	map<std::string, vector<Produs>> raport(string field);
	//salveaza cosul de cumparaturi in fisier
	void exporta(string nume_fisier);
	void undo();
	Cos& getCos();
	double get_pret_cos();
	
};

void teste_service();

void test_filtrari();
void test_raport();
bool comp_nume(Produs x, Produs y);
bool comp_pret(Produs x, Produs y);
bool comp_nume_tip(Produs x, Produs y);