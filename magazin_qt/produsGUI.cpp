#include "produsGUI.h"
#include <exception>


	void ProdusGui::adauga_butoane() {
		QLayoutItem* item;
		while ((item = ly_btn_din->takeAt(0)) != nullptr) {
			delete item->widget();
			delete item;
		}
		map<std::string, int> my_map;
		for (const auto& p : mag.get_all()) {
			if (my_map.find(p.get_producator()) == my_map.end())
				my_map[p.get_producator()] = 1;
			else my_map[p.get_producator()]++;

		}
		for (auto it = my_map.begin(); it != my_map.end(); it++) {
			auto number = it->second;
			auto btn = new QPushButton{ QString::fromStdString(it->first) };
			ly_btn_din->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [&my_map, number]() {
				QMessageBox::information(nullptr, "", QString::number(number));

				});
		}

	}


	void ProdusGui::loadData(std::vector<Produs> prod) {
		MyTableModel* model = new MyTableModel(this);
		lista_curenta = std::move(prod);
		model->setproduse(lista_curenta);
		lst->setModel(model);
		connect_list( prod);
		adauga_butoane();
		
}
	void ProdusGui::initconnect() {
		QObject::connect(btn_add,
			&QPushButton::clicked, [this]()
			{

				auto nume = txtNume->text().toStdString();
				auto producator = txtProducator->text().toStdString();
				auto tip = txtTip->text().toStdString();
				auto pret = txtPret->text().toStdString();
				if (nume.empty() or producator.empty() or tip.empty() or pret.empty() ) {
					QMessageBox::information(this, "something wrong", "someting wrong");
					return;

				}
				try {
					auto pret_numeric = txtPret->text().toDouble();
					mag.adauga(pret_numeric, nume, producator, tip);
				}
				catch (ValidError& msg) {
					QMessageBox::information(this, "something wrong", "someting wrong");
					return;

				}
				catch (RepoException& msg) {
					QMessageBox::information(this, "something wrong", "someting wrong");
					return;

				}
				loadData(mag.get_all());
				txtNume->clear();
				txtPret->clear();
				txtProducator->clear();
				txtTip->clear();
	
			});
		QObject::connect(btn_upt,
			&QPushButton::clicked, [this]() {

				auto index = selectedIndex();
				if (index == -1)
				{
					QMessageBox::information(this, "nothing selected", "nothing selected");
					return;
				}

				auto nume = txtNume->text().toStdString();
				auto producator = txtProducator->text().toStdString();
				auto tip = txtTip->text().toStdString();
				auto pret = txtPret->text().toStdString();
				if (nume.empty() or producator.empty() or tip.empty() or pret.empty())
				{
					QMessageBox::information(this, "something went wrong", "something went wrong");
					return;
				}
				auto pret_numeric = txtPret->text().toDouble();
				try {
					mag.modifica(pret_numeric, nume, producator, tip);
					auto p = Produs(pret_numeric, nume, producator, tip);
				}
				catch (RepoException& msg) { QMessageBox::information(this, "something went wrong", "something wrong"); }
				   catch(ValidError& msg){ QMessageBox::information(this, "something went wrong", "nu poti modifica numele"); }
				loadData(mag.get_all());
				txtNume->clear();
				txtProducator->clear();
				txtPret->clear();
				txtTip->clear();

			});
		QObject::connect(btn_del,
			&QPushButton::clicked,
			[this]() {
				auto index = selectedIndex();
				if (index == -1) {
					QMessageBox::information(this, "nothing selected", "nothing selected");
					return;

				}
				auto nume = txtNume->text().toStdString();
				if (nume == "") {
					QMessageBox::information(this, "nothing selected", "nothing selected");
					return;
				}
				mag.sterge(nume);
				
				auto producator = txtProducator->text().toStdString();
				auto tip = txtTip->text().toStdString();
				auto pret_numeric = txtPret->text().toDouble();
				auto p = Produs(pret_numeric, nume, producator, tip);
				try {
					qDebug() << "incearca sa incarce datele";
					loadData(mag.get_all());
				}
				catch (std::exception) {
					QMessageBox::information(this, "something went wrong", "something wrong");
				}
				txtNume->clear();
				txtProducator->clear();
				txtPret->clear();
				txtTip->clear();


			});

		QObject::connect(btn_filtrare_pret,
			&QPushButton::clicked, [this]() {
				auto pret_minim = txtpret_min->text().toDouble();
				loadData(mag.filtrare_pret(pret_minim));
			});
		QObject::connect(btn_filtrare_nume,
			&QPushButton::clicked, [this]() {
				auto nume = txt_filtrare_nume->text().toStdString();

				loadData(mag.filtrare_nume(nume));
			});
		QObject::connect(btn_filtrare_producator,
			&QPushButton::clicked, [this]() {
				auto producator = txt_producator_filtrare->text().toStdString();

				loadData(mag.filtrare_producator(producator));
			});
		QObject::connect(btn_sort_nume,
			&QPushButton::clicked,
			[this]() {loadData(mag.sortare(comp_nume)); }
		);
		QObject::connect(btn_sort_pret,
			&QPushButton::clicked,
			[this]() {loadData(mag.sortare(comp_pret)); }
		);
		QObject::connect(btn_sort_nume_tip,
			&QPushButton::clicked,
			[this]() {loadData(mag.sortare(comp_nume_tip)); }
		);

		QObject::connect(cos, &QPushButton::clicked,
			[this]() {
				auto nume = txtNume->text().toStdString();
				if (nume == "") {
					
						QMessageBox::information(this, "something wrong", "someting wrong");
						return;


				}
				mag.adauga_produs_cos(nume);
				QMessageBox::information(this, "pretul cosului este:", QString::number(mag.get_pret_cos()));
				txtNume->clear();
				txtProducator->clear();
				txtPret->clear();
				txtTip->clear();
			});
		QObject::connect(goleste_cos, &QPushButton::clicked,
			[this]() {

				mag.goleste_cos();
				QMessageBox::information(this, "pretul cosului este:", QString::number(mag.get_pret_cos()));
			});
		QObject::connect(adauga_random, &QPushButton::clicked,
			[this]() {
				auto howMany = adauga_random_text->text().toInt();
				mag.adauga_produse_random(howMany);
				QMessageBox::information(this, "pretul cosului este:", QString::number(mag.get_pret_cos()));
				adauga_random_text->clear();
			});
		QObject::connect(salv_cos, &QPushButton::clicked, [this]() {
			auto nume_fisier = fisier->text().toStdString();
			if (nume_fisier == "") {
				QMessageBox::information(this, "error", "error");
				return;}
			mag.exporta(nume_fisier);
			fisier->clear();
			});
		QObject::connect(undo, &QPushButton::clicked, [this]() {
			try { mag.undo(); loadData(mag.get_all()); }
			catch (std::exception) {

				QMessageBox::information(this, "nu se mai poate face undo", "nu se mai poate face undo");
				return;

			}});
		QObject::connect(deschide_cos, &QPushButton::clicked, [this]() {

			CosGUI* cosGUI = new CosGUI(mag);
			mag.register_observer(cosGUI);
		    cosGUI->show();
		});
		QObject::connect(CosREAD, &QPushButton::clicked, [this]() {
			Desen* cosGUI = new Desen(mag);
			mag.register_observer(cosGUI);
			cosGUI->show();
			});

	}
	int ProdusGui::selectedIndex() {
		auto index = lst->selectionModel()->currentIndex();
		if (!index.isValid())return -1;
		return index.row();
	}
	void ProdusGui::initGui() {


		lyMain->addWidget(lst);
		setLayout(lyMain);
		QVBoxLayout* liSTG = new QVBoxLayout;
		liSTG->addWidget(btn_add);
		liSTG->addWidget(btn_del);
		liSTG->addWidget(btn_upt);
		QFormLayout* lst_param = new QFormLayout;
		lst_param->addRow("Nume:", txtNume);
		lst_param->addRow("Producator:", txtProducator);
		lst_param->addRow("Tip:", txtTip);
		lst_param->addRow("pret:", txtPret);
		lst_param->addWidget(btn_sort_nume);
		lst_param->addWidget(btn_sort_pret);
		lst_param->addWidget(btn_sort_nume_tip);
	    lst_param->addWidget(cos);
		lst_param->addWidget(goleste_cos);
		lst_param->addWidget(undo);
		lst_param->addWidget(deschide_cos);
		lst_param->addWidget(CosREAD);
		liSTG->addLayout(lst_param);
		lyMain->addLayout(liSTG);
		lyMain->addLayout(prod_layout);

		btn_din->setLayout(ly_btn_din);
		lyMain->addWidget(btn_din);
		QVBoxLayout* filtrari = new QVBoxLayout;
		QVBoxLayout* filtrari_spatii = new QVBoxLayout;
		filtrari->addWidget(btn_filtrare_pret);
		filtrari_spatii->addWidget(txtpret_min);
		filtrari->addWidget(btn_filtrare_nume);
		filtrari_spatii->addWidget(txt_filtrare_nume);
		filtrari->addWidget(btn_filtrare_producator);
		filtrari_spatii->addWidget(txt_producator_filtrare);
		filtrari->addWidget(adauga_random);
		filtrari_spatii->addWidget(adauga_random_text);
		filtrari->addWidget(salv_cos);
		filtrari_spatii->addWidget(fisier);
		lyMain->addLayout(filtrari);
		lyMain->addLayout(filtrari_spatii);
	}

	void ProdusGui::connect_list(std::vector<Produs> prod)
	{
		QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			auto index = selectedIndex();
			if (index == -1) {
				QMessageBox::information(this, "something went wrong", "something went wrong");
				return;
			}
			auto p = lista_curenta[index];
			txtNume->setText(QString::fromStdString(p.get_nume()));
			txtProducator->setText(QString::fromStdString(p.get_producator()));
			txtTip->setText(QString::fromStdString(p.get_tip()));
			txtPret->setText(QString::number(p.get_price()));
			});
	}



