#include "service.h"
#include "assert.h"
#include <iostream>
#include<algorithm>
#include<exception>
#include "fileexception.h"
void Magazin::adauga(double pret, string nume, string producator, string tip)
{   
	Produs p{pret, nume, producator, tip };
	validator.valideaza(p);
	rep.store(p);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, p));
}

void Magazin::modifica(double pret_nou, string nume, string producator_nou, string tip_nou)
{
	Produs p = Produs(pret_nou, nume, producator_nou, tip_nou);
	validator.valideaza(p);
	auto p_vechi = *rep.cauta(nume);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, p_vechi));
	rep.modifica(nume, p);
	
}

void Magazin::sterge(string nume)
{
	
	vector<Produs> :: iterator poz = rep.cauta(nume);
	Produs p = *poz;
	rep.sterge(nume);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, p));
	
}

const vector<Produs> Magazin::get_all() const
{
	return rep.get_all();
}

 size_t Magazin::size() const
{
	return rep.size();
}

 

 const vector<Produs> Magazin::filtrare_pret(double pret_minim) const
 {
	 vector<Produs> produse = rep.get_all();
	 vector<Produs> produse_filtrate;

	  std::copy_if(produse.begin(), produse.end(), back_inserter(produse_filtrate), [&pret_minim](Produs& p) {return p.get_price() > pret_minim; });
	 return produse_filtrate;
 }

 const vector<Produs> Magazin::filtrare_nume(string nume) const
 {
	 vector<Produs> produse = rep.get_all();
	 vector<Produs> produse_filtrate;
	 std::copy_if(produse.begin(), produse.end(), back_inserter(produse_filtrate), [&nume](const Produs& p) {return p.get_nume() == nume; });
	 return produse_filtrate;
 }


 const vector<Produs> Magazin::filtrare_producator(string producator) const
 {
	 vector<Produs> produse = rep.get_all();
	 vector<Produs> produse_filtrate;
	 std::copy_if(produse.begin(), produse.end(), back_inserter(produse_filtrate), [&producator](const Produs& p) {return p.get_producator() == producator; });
	 return produse_filtrate;
 }



 vector<Produs> Magazin::sortare(compara cmp)
 {  

	 
	 vector<Produs> produse = rep.get_all();
	 std::sort(produse.begin(), produse.end(), cmp);
	 return produse;
 }

 void Magazin::adauga_produs_cos(string nume) {

	 std::vector<Produs>::iterator poz = rep.cauta(nume);
	 Produs p = *poz;
	 cos.adauga_produs_in_cos(p);
	 this->notify();

 }

 void Magazin::adauga_produse_random(int howMany) {
	
	 cos.adauga_random_cos(rep.get_all(), howMany);
	 this->notify();
 }
 void Magazin::goleste_cos() { 
	 
	 cos.goleste_cos();
	 this->notify();
 }
 const vector<Produs> Magazin:: get_all_cos() {
	 return cos.get_all_cos();
		}
 bool comp_nume(Produs x, Produs y)
 {
	 return x.get_nume() < y.get_nume();
 }

 bool comp_pret(Produs x, Produs y)
 {
	 return x.get_price() <y.get_price();
 }

 bool comp_nume_tip(Produs x, Produs y)
 {
	 if (x.get_nume() == y.get_nume())
		 return x.get_tip() < y.get_tip();
	 return comp_nume(x,y);
 }

 map<std::string, std::vector<Produs>> Magazin::raport(string field) {
	 map<std::string,std::vector<Produs>> my_map;
	 vector<Produs> produse = rep.get_all();
	 if(field=="producator")
	 for (const auto& produs : produse)
	 {
		 auto producator = produs.get_producator();
		
		 my_map[producator].push_back(produs);
}
	 if (field == "nume")
	 for (const auto& produs : produse)
	 {
		 auto nume = produs.get_nume();

		 my_map[nume].push_back(produs);
	 }
	 if (field == "tip")
	 for (const auto& produs : produse)
	 {
		 auto tip = produs.get_tip();

		 my_map[tip].push_back(produs);
	 }
	 return my_map;
}

 void Magazin::exporta(string nume_fisier)
 {

	
	 std::ofstream g(nume_fisier);

	 if (!g.is_open())
		 throw File_Error("fisierul nu s-a putut deschide");

	 auto lista_produse = cos.get_all_cos();

	 for (const auto& produs : lista_produse)
		g<< produs << "\n";
	 g.close();
 }

 void Magazin::undo()
 {
	 if (undoActions.empty())throw std::exception("nu se mai poate face undo");
	 undoActions.back()->doUndo();
	 undoActions.pop_back();

 }

 Cos& Magazin::getCos()
 {
	 return cos;
 }

 double Magazin::get_pret_cos()
 {
	 vector<Produs> produse = get_all_cos();
	 double pret_cos = 0;
	 for (const auto& produs : produse) {
		 pret_cos += produs.get_price();

	 }
	 return pret_cos;
 }


void teste_service() {
	
	Repo rep;
	Validator valid;
	Cos cos;
	 Magazin mag{ rep , valid,cos };

	mag.adauga(1.22, "banana", "africa", "bune");
	mag.adauga(2.22, "covrig", "petru", "sare");

	mag.adauga(51.22, "laptop", "lenovo", "gaming");
	mag.undo();
	assert(mag.size() == 2);
	mag.adauga(51.22, "laptop", "lenovo", "gaming");
	mag.modifica(5, "banana", "india", "rele");
	vector<Produs> vect = mag.get_all();
	
	assert(vect[0].get_nume() == "banana");
	assert(vect[0].get_producator() == "india");
	assert(vect[0].get_tip() == "rele");
	mag.undo();
	vect = mag.get_all();
	assert(vect[0].get_nume() == "banana");
	assert(vect[0].get_producator() == "africa");
	assert(vect[0].get_tip() == "bune");
	mag.sterge("banana");
	assert(mag.size() == 2);
	mag.undo();
	assert(mag.size() == 3);

}
void test_filtrari() {

	Repo rep;
	Validator valid;
	Cos cos;
	Magazin mag{ rep , valid ,cos};
	mag.adauga(1.22, "macos", "apple", "linux");
	mag.adauga(2.22, "macos", "apple", "ubuntu");

	mag.adauga(51.22, "laptop", "lenovo", "gaming");

	assert(mag.filtrare_nume("macos").size() == 2);
	assert(mag.filtrare_producator("apple").size() == 2);
	assert(mag.filtrare_pret(25).size() == 1);
	vector<Produs> lista=mag.sortare(comp_nume_tip);

	assert(lista[0].get_tip() == "gaming");
	assert(lista[1].get_tip() == "linux");
	assert(lista[2].get_tip() == "ubuntu");
	lista = mag.sortare(comp_pret);

	assert(lista[0].get_price() == 1.22);
	assert(lista[1].get_price() == 2.22);
	assert(lista[2].get_price() == 51.22);

	mag.adauga_produse_random(2);
	mag.adauga_produs_cos("macos");
	assert(mag.get_all_cos().size() == 3);
	mag.goleste_cos();
    assert(mag.get_all_cos().size() == 0);
	

}

void test_raport() {
	Repo rep;
	Validator valid;
	Cos cos;
	Magazin mag{ rep , valid ,cos };
	mag.adauga(1.22, "macos", "apple", "linux");
	mag.adauga(2.22, "macos", "apple", "ubuntu");

	mag.adauga(51.22, "laptop", "lenovo", "gaming");
	auto my_map = mag.raport("producator");
	assert(my_map["apple"].size() == 2);
	assert(my_map["lenovo"].size() == 1);

    my_map = mag.raport("tip");
	assert(my_map["linux"].size() == 1);
	assert(my_map["gaming"].size() == 1);
	assert(my_map["ubuntu"].size() == 1);

	my_map = mag.raport("nume");
	assert(my_map["macos"].size() == 2);
	assert(my_map["laptop"].size() == 1);
	auto lista_prod = mag.get_all();
	mag.adauga_produse_random(5);


	mag.exporta("file_test");
	std::ifstream g("file_test");
	assert(g.peek() != std::ifstream::traits_type::eof());
	g.close();
}




