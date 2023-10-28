#include "cosGUI.h"

void CosGUI::Init()
{
	setLayout(mainLayout);
	//mainLayout->addWidget(prodWidget);
	mainLayout->addWidget(table);
	
	QVBoxLayout* box = new QVBoxLayout;
	QVBoxLayout* butoane = new QVBoxLayout;
	butoane->addWidget(adauga);
	butoane->addWidget(adauga_normal);
	butoane->addWidget(save);
	butoane->addWidget(goleste);
	box->addWidget(line);

	mainLayout->addLayout(butoane);
	mainLayout->addLayout(box);
}

void CosGUI::Connect()
{
   // QTimer* refreshTimer = new QTimer;
	//QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
	//	loadlist(mag.get_all_cos());
	//	});
	//refreshTimer->start(1000);
	QObject::connect(adauga, &QPushButton::clicked, [this]() {
		auto howMany = line->text().toInt();
	mag.adauga_produse_random(howMany);
	loadlist(mag.get_all_cos());
});
	QObject::connect(adauga_normal, &QPushButton::clicked, [this]() {
		auto nume = line->text().toStdString();
		try {
			mag.adauga_produs_cos(nume);
			
			loadlist(mag.get_all_cos());
		}
		catch (RepoException& eroare) {
			auto mes = QString::fromStdString(eroare.get_message());
			QMessageBox::information(this, mes, mes);

		}
		});
	QObject::connect(save, &QPushButton::clicked, [this]() {
		auto nume_fisier = line->text().toStdString();
		if (nume_fisier == "") {
			QMessageBox::information(this, "error", "error");
			return;
		}
		mag.exporta(nume_fisier);
		fisier->clear();
		loadlist(mag.get_all_cos());

		});
	QObject::connect(goleste, &QPushButton::clicked,
		[this]() {

			mag.goleste_cos();
			loadlist(mag.get_all_cos());
			
			
		});
}

void CosGUI::loadlist(const vector<Produs>& prods)
{
	MyTableModel* model = new MyTableModel(this);
	model->setproduse(prods);
	table->setModel(model);


}
void CosGUI::update() {
	loadlist(mag.get_all_cos());

};