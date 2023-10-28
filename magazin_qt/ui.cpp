#include "ui.h"
#include<iostream>
#include "sortare.h"
#include "fileexception.h"

using std::cout;
using std::cin;
void UI::adaugaUI() {
	double pret;
	string nume, producator, tip;
	cout << "nume:";
	cin >> nume;
	cout << "producator:";
	cin >> producator;
	cout << "tip:";
	cin >> tip;
	cout << "pret:";
	cin >> pret;
	mag.adauga(pret, nume, producator, tip);
	cout << "produs adaugat\n";
}
void UI::tiparesteUI() {
	vector<Produs> produse = mag.get_all();
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}
} 

void UI::modificaUI() {
	double pret;
	string nume, producator, tip;
	cout << "nume:";
	cin >> nume;
	cout << "producator:";
	cin >> producator;
	cout << "tip:";
	cin >> tip;
	cout << "pret:";
	cin >> pret;
	mag.modifica(pret,nume,producator,tip);
	cout << "produs modificat\n";

}
void UI::stergeUI() {
	string nume;
	cout << "nume:";
	cin >> nume;
	mag.sterge(nume);
	cout << "produs sters\n";
}
void UI::filtrareUI()
{
	vector<Produs> produse;
	int caz;
	cout << "dupa ce vrei sa filtrezi ?\npret:1\nnume:2\nproducator:3\n";
	cin >> caz;
	switch (caz)
	{
	case 1:
	{cout << "pretul:";
	double pret;
	cin >> pret;
	produse = mag.filtrare_pret(pret);
	break; }
	case 2:
	{cout << "nume:";
	string nume;
	cin >> nume;
	produse = mag.filtrare_nume(nume);
	break; }
	case 3:
	{cout << "producator:";
	string producator;
	cin >> producator;
	produse = mag.filtrare_producator(producator);
	break; }
	default:break;
}
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}

}


void UI::sortareUI()
{
	vector<Produs> produse;
	cout << "dupa ce vrei sa sortezi? \n1:nume\n2:pret\n3:nume+tip\n";
	int caz;
	cin >> caz;
	switch (caz) {
	case 1:
		produse = mag.sortare(comp_nume);
		break;
	case 2:
		produse = mag.sortare(comp_pret);
		break;
	case 3:
		produse = mag.sortare(comp_nume_tip);
		break;
	default:break;

	}
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}

}

void UI::adauga_cosUI()
{
	string nume;
	cout << "introdu numele:";
	cin >> nume;
	mag.adauga_produs_cos(nume);

}

void UI::goleste_cosUI()
{
	mag.goleste_cos();
}

void UI::adauga_random_cosUI()
{
	int howMany;
	cout << "cate vrei sa adaugi:";
	cin >> howMany;
	mag.adauga_produse_random(howMany);
}

void UI::tipareste_cosUI()
{
	vector<Produs> produse = mag.get_all_cos();
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}
}

double UI::get_pret_UI()
{
	vector<Produs> produse = mag.get_all_cos();
	double pret_cos=0;
	for (const auto& produs : produse) {
		pret_cos += produs.get_price();

	}
	return pret_cos;
}

void UI::report()
{
	cout << "1 producator\n2 nume\n3 tip\n";
	int caz;
	std::string field;
	cin >> caz;
	switch (caz) {
	case 1:
		field = "producator";
		break;
	case 2:
		field = "nume";
		break;
	case 3:
		field = "tip";
		break;
	default:break;

	}
	auto my_map = mag.raport(field);

	for (auto it = my_map.begin(); it != my_map.end(); it++)
	{
		
		cout <<field<<" "<< it->first << ": ";
		for (auto i = 0;i<it->second.size(); i++)
			cout << it->second[i].get_nume()<<" ";
		cout << '\n';

	}

}

void UI::exportaUI()
{
	cout << "numele fisierului este:";
	string nume_fisier;
	int opt;
	cin >> nume_fisier;
	cout << "1.CSV\n2.HTML\n";
	cin >> opt;
	if (opt == 2)nume_fisier += ".html";
	mag.exporta(nume_fisier);
	cout << "cosul a fost salvat\n";

}

void UI::undoUI()
{
	try {
		mag.undo();
	}
	catch (std::exception& msg) {
		cout << "nu se poate face undo\n";
}
}

void UI::run()
{
	int cmd ;
	while (true) {
		cout << "Meniu\n";
		cout << "1 adauga\n2 tipareste\n3 modifica\n4 sterge\n5 filtrare\n6 sortare\n7 adauga cos\n8 goleste cos\n9 adauga random\n10 tipareste cos\n11 raport\n12 export\n13 UNDO\n0 exit\n";
		cin >> cmd;
		try {
			switch (cmd)
			{
			
			case 0:return;
			
			case 1:
				adaugaUI();
				break;
			case 2:
				tiparesteUI();
				break;
			case 3:
				modificaUI();
				break;
			case 4:
				stergeUI();
				break;
			case 5:
				filtrareUI();
				break;
			case 6:
				sortareUI();
				break;
			case 7:
				adauga_cosUI();
				cout << "pretul cosului este:"<<get_pret_UI()<<" lei\n";
				break;
			case 8:
				goleste_cosUI();
				cout << "pretul cosului este:" << get_pret_UI() << " lei\n";
				break;
			case 9:
				adauga_random_cosUI();
				cout << "pretul cosului este:" << get_pret_UI() << " lei\n";
				break;
			case 10:
				tipareste_cosUI();
				cout << "pretul cosului este:" << get_pret_UI() << " lei\n";
				break;
			case 11:
				report();
				break;
			case 12:
				exportaUI();
				break;
			case 13:
				undoUI();
				break;
			default:cout << "comanda invalida\n";
			}
		}
		catch (RepoException& ex) {
			cout << ex.get_message()<<'\n';
		}
		catch (ValidError& ex) {
			cout << ex.get_message() << '\n';

		}
		catch (File_Error& ex) {
			cout << ex.get_message() << '\n';
}
	}
}

	

