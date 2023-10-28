#include "file_repo.h"
#include <fstream>
#include "fileexception.h"
void RepoFile::loadFromFile()
{
	std::ifstream in(fName);
	if (!in.is_open()) {
		//verify if the stream is opened
		throw File_Error("Error open:" + fName);
	}
	while (!in.eof()) {
		if (in.eof()) break;
		std::string type,nume,producator;
		double price;
		in >> nume;
		in >> producator;
		in >> type;
		in >> price;
		
		if (nume != "")
		{
			Produs p(price, nume.c_str(), producator.c_str(), type.c_str());
	         produse.push_back(p);
		}
	}
	in.close();
}



void RepoFile::writeToFile()
{
	std::ofstream out(fName);
	if (!out.is_open()) {
		
			//verify if the stream is opened
			std::string msg("Error open file");
		throw File_Error(msg);
	}
	for (auto& p : get_all()) {
		
		out << p.get_nume() << "\n";
		out << p.get_producator() << "\n";
		out << p.get_tip() << "\n";
		out << p.get_price()<< "\n";
	}
	out.close();

}

void test_file_repo()
{   

	std::ofstream g("fisier_test");


	if (!g.is_open())
		throw File_Error("fisierul nu s-a putut deschide");


	RepoFile lista("fisier_test");
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
	RepoFile lista2("fisier_test");
	assert(lista2.size() == 1);
}
