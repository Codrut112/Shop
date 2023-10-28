#pragma once
#include <QtWidgets/qapplication.h>
#include <QtWidgets/Qwidget>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout>
#include <qlistview.h>
#include <QMessageBox>
#include <QGroupBox>
#include "service.h"
#include "cosGUI.h"
#include "observer.h"
#include "draw.h"
#include "model.h"

class ProdusGui :public QWidget,public Subject {
private:
	QHBoxLayout* lyMain = new QHBoxLayout{};
	QListView* lst = new QListView;
	QPushButton* btn_add = new QPushButton("adauga");
	QPushButton* btn_del = new QPushButton("sterge");
	QPushButton* btn_upt = new QPushButton("modifica");
	QPushButton* btn_filtrare_pret = new QPushButton("filtrare pret");
	QPushButton* btn_filtrare_nume = new QPushButton("filtrare nume");
	QPushButton* btn_filtrare_producator = new QPushButton("filtrare producator");
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txt_producator_filtrare = new QLineEdit;
	QHBoxLayout* prod_layout = new QHBoxLayout;
	QWidget* btn_din = new QWidget;
	QLineEdit* txtpret_min = new QLineEdit;
	QLineEdit* txt_filtrare_nume = new QLineEdit;
	QPushButton* btn_sort_nume = new QPushButton("sortare dupa nume");
	QPushButton* btn_sort_pret = new QPushButton("sortare dupa pret");
	QPushButton* btn_sort_nume_tip = new QPushButton("sortare dupa nume si tip");
	QPushButton* cos = new QPushButton("adauga cos");
	QPushButton* adauga_random = new QPushButton("adauga random cos");
	QPushButton* goleste_cos = new QPushButton("goleste_cos");
	QVBoxLayout* ly_btn_din = new QVBoxLayout;
	QLineEdit* adauga_random_text = new QLineEdit;
	QPushButton* salv_cos = new QPushButton("salveaza cos");
	QLineEdit* fisier = new QLineEdit;
	QPushButton* undo = new QPushButton("undo");
	Magazin& mag;
	QPushButton* deschide_cos = new QPushButton("CosCRUDGUI");
	QPushButton* CosREAD = new QPushButton("CosREADOnlyGUI");
	vector<Observer*> cosuri;
	vector<Produs> lista_curenta;
	//adauga butoanele dinamice
	void adauga_butoane();
	//incarca datele din fisier
	void loadData(std::vector<Produs> prod);
	void initconnect();
	//returneaza indexul elementului selectat
	int selectedIndex();
	void initGui();
	void connect_list(std::vector<Produs> prod);
	
public:
	ProdusGui(Magazin& mag) :mag{ mag } { 

		initGui(); loadData(mag.get_all()); initconnect(); };
	
};